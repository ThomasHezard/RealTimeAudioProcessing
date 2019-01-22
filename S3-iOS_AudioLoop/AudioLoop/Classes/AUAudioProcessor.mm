//
//  AUAudioProcessor.m
//  AudioLoop
//
//  Created by Thomas Hézard on 2019/02/02.
//  Copyright © 2019 THZ. All rights reserved.
//

#import "AUAudioProcessor.h"
#import "audio_processor.h"
#import <mutex>


@interface AUAudioProcessor()

@property (nonatomic, strong)       AVAudioFormat *             outputFormat;
@property (nonatomic, strong)       AUAudioUnitBus *            outputBus;
@property (nonatomic, strong)       AUAudioUnitBusArray *       outputBusArray;

@property (nonatomic, strong)       AVAudioFormat *             inputFormat;
@property (nonatomic, strong)       AUAudioUnitBus *            inputBus;
@property (nonatomic, strong)       AUAudioUnitBusArray *       inputBusArray;
@property (nonatomic, strong)       AVAudioPCMBuffer *          inputBuffer;

@property (nonatomic, strong)       NSArray<NSNumber*> *        channelCapabilities;

@end


@implementation AUAudioProcessor {
    
    AudioProcessor *            _processor;
    std::mutex                  _renderingMutex;
    AudioBufferList *           _inputABL;
    
}


@synthesize channelCapabilities;


+ (void) registerAudioUnitAndBuildDescription:(AudioComponentDescription*)description {
    
    description->componentType = kAudioUnitType_Effect;
    description->componentManufacturer = 0x54485a20; // 'THZ '
    description->componentSubType = 0x41755072; // 'AuPr'
    description->componentFlags = 0;
    description->componentFlagsMask = 0;
    static dispatch_once_t AUAudioProcessorRegistrationToken;
    dispatch_once(&AUAudioProcessorRegistrationToken, ^{
        [AUAudioUnit registerSubclass:AUAudioProcessor.self asComponentDescription:*description name:@"AUAudioProcessor" version:1];
    });
}


- (instancetype)initWithComponentDescription:(AudioComponentDescription)componentDescription
                                       error:(NSError * _Nullable __autoreleasing *)outError {
    
    return [self initWithComponentDescription:componentDescription options:0 error:outError];
}


- (instancetype)initWithComponentDescription:(AudioComponentDescription)componentDescription
                                     options:(AudioComponentInstantiationOptions)options
                                       error:(NSError * _Nullable __autoreleasing *)outError {
    
    @synchronized(self) {
        
        self = [super initWithComponentDescription:componentDescription options:options error:outError];
        
        if (self) {
            
            // default values
            
            self.maximumFramesToRender = 4096;
            
            float defaultSampleRate = 48000;
            
            _processor = new AudioProcessor{};
            
            self.outputFormat = [[AVAudioFormat alloc] initWithCommonFormat:AVAudioPCMFormatFloat32
                                                                 sampleRate:defaultSampleRate
                                                                   channels:1
                                                                interleaved:NO];
            
            self.outputBus = [[AUAudioUnitBus alloc] initWithFormat:self.outputFormat error:outError];
            self.outputBusArray = [[AUAudioUnitBusArray alloc] initWithAudioUnit:self
                                                                         busType:AUAudioUnitBusTypeOutput
                                                                          busses:@[self.outputBus]];
            
            self.inputFormat = [[AVAudioFormat alloc] initWithCommonFormat:AVAudioPCMFormatFloat32
                                                                sampleRate:defaultSampleRate
                                                                  channels:1
                                                               interleaved:NO];
            
            self.inputBus = [[AUAudioUnitBus alloc] initWithFormat:self.inputFormat error:outError];
            self.inputBusArray = [[AUAudioUnitBusArray alloc] initWithAudioUnit:self
                                                                        busType:AUAudioUnitBusTypeInput
                                                                         busses:@[self.inputBus]];
            
            NSMutableArray<NSNumber*> *supportedNumberChannels = [[NSMutableArray<NSNumber*> alloc] initWithCapacity:2];
            supportedNumberChannels[0] = [NSNumber numberWithInt:1];
            supportedNumberChannels[1] = [NSNumber numberWithInt:1];
            self.channelCapabilities = [NSArray<NSNumber*> arrayWithArray:supportedNumberChannels];
        }
        
        return self;
    }
}


- (void) dealloc {
    
    _renderingMutex.lock();
    @synchronized (self) {
        delete _processor;
        _renderingMutex.unlock();
    }
}


- (AUAudioUnitBusArray *)outputBusses {
    return _outputBusArray;
}


- (AUAudioUnitBusArray *)inputBusses {
    return _inputBusArray;
}


- (BOOL)shouldChangeToFormat:(AVAudioFormat *)format forBus:(AUAudioUnitBus *)bus {
    
    @synchronized (self) {
        return [self internalShouldChangeToFormat:format forBus:bus];
    }
    
}


- (BOOL)internalShouldChangeToFormat:(AVAudioFormat *)format forBus:(AUAudioUnitBus *)bus {
    
    if (self.renderResourcesAllocated) {
        return NO;
    }
    
    if (bus == _outputBus) {
        NSError *error = nil;
        return [self setOutputFormat:format error:&error];
    }
    
    if (bus == _inputBus) {
        NSError *error = nil;
        return [self setInputFormat:format error:&error];
    }
    
    return NO;
}


- (BOOL) setOutputFormat:(AVAudioFormat*)outputFormat error:(NSError**)error {
    
    if (self.renderResourcesAllocated) {
        return NO;
    }
    if (outputFormat.commonFormat != self.outputFormat.commonFormat ||
        outputFormat.channelCount != self.outputFormat.channelCount ||
        outputFormat.sampleRate != self.outputFormat.sampleRate) {
        return NO;
    }
    self.outputFormat = outputFormat;
    return YES;
}


- (BOOL) setInputFormat:(AVAudioFormat*)inputFormat error:(NSError**)error {
    
    if (self.renderResourcesAllocated) {
        return NO;
    }
    if (inputFormat.commonFormat != self.inputFormat.commonFormat ||
        inputFormat.channelCount != self.inputFormat.channelCount ||
        inputFormat.sampleRate != self.inputFormat.sampleRate) {
        return NO;
    }
    self.inputFormat = inputFormat;
    return YES;
}


- (BOOL)allocateRenderResourcesAndReturnError:(NSError * _Nullable __autoreleasing *)outError {
    
    _renderingMutex.lock();
    @synchronized (self) {
        BOOL result = [super allocateRenderResourcesAndReturnError:outError];
        if (!result) {
            return NO;
        }
        self.inputBuffer = [[AVAudioPCMBuffer alloc] initWithPCMFormat:self.inputFormat frameCapacity:self.maximumFramesToRender];
        _inputABL = self.inputBuffer.mutableAudioBufferList;
        _renderingMutex.unlock();
        return YES;
    }
}


- (void)deallocateRenderResources {
    
    _renderingMutex.lock();
    @synchronized (self) {
        _inputABL = NULL;
        self.inputBuffer = nil;
        [super deallocateRenderResources];
        _renderingMutex.unlock();
    }
}


- (void) reset {
    
    @synchronized (self) {
        [super reset];
    }
}


- (AUInternalRenderBlock)internalRenderBlock {
    
    __block AudioProcessor **           processor = &_processor;
    
    __block std::mutex *                renderingMutex = &_renderingMutex;
    
    __block AudioBufferList **          inputABL = &_inputABL;
    
    return ^AUAudioUnitStatus(
                              AudioUnitRenderActionFlags *actionFlags,
                              const AudioTimeStamp       *timestamp,
                              AVAudioFrameCount           frameCount,
                              NSInteger                   outputBusNumber,
                              AudioBufferList            *outputData,
                              const AURenderEvent        *realtimeEventListHead,
                              AURenderPullInputBlock      pullInputBlock) {
        
        /// Check lock status
        if ((*renderingMutex).try_lock()) {
            
            // Check ressources allocation
            if (*inputABL == NULL) {
                (*renderingMutex).unlock();
                return -1;
            }
            
            // Prepare input ABL
            uint32_t inputBytesPerFrame = sizeof(Float32);
            UInt32 inputByteSize =  frameCount * inputBytesPerFrame;
            (*inputABL)->mBuffers[0].mNumberChannels = 1;
            (*inputABL)->mBuffers[0].mDataByteSize = inputByteSize;
            
            // Pulling input
            AUAudioUnitStatus inputStatus = pullInputBlock(actionFlags, timestamp, frameCount, 0, *inputABL);
            if (inputStatus) {
                (*renderingMutex).unlock();
                return inputStatus;
            }
            
            // ********** Processing **********
            
            // Check outputData buffer allocation and copy inputData if needed
            uint32_t outputBytesPerFrame = sizeof(Float32);
            UInt32 outputByteSize =  frameCount * outputBytesPerFrame;
            outputData->mBuffers[0].mNumberChannels = 1;
            outputData->mBuffers[0].mDataByteSize = outputByteSize;
            if (outputData->mBuffers[0].mData == NULL) {
                outputData->mBuffers[0].mData = (*inputABL)->mBuffers[0].mData;
            } else {
                memcpy(outputData->mBuffers[0].mData, (*inputABL)->mBuffers[0].mData, outputByteSize);
            }
            
            // Internal process
            (*processor)->Process(static_cast<float*>(outputData->mBuffers[0].mData), static_cast<int>(frameCount));
            
            // Return value
            (*renderingMutex).unlock();
            *actionFlags &= !kAudioUnitRenderAction_OutputIsSilence;
            return noErr;
            
        }
        
        // Failing to lock means AU is deallocating its ressources or updating its process.
        // Hence, we suppose we're in a scenario where the AU is supposed to output silence.
        else {
            
            *actionFlags |= kAudioUnitRenderAction_OutputIsSilence;
            return noErr;
            
        }
    };
}


- (void)setParam:(int)paramID value:(float)value {
    if (_processor) {
        _processor->set_param(paramID, value);
    }
}


- (float)getParam:(int)paramID {
    return _processor != nullptr ? _processor->get_param(paramID) : 0.0f;
}


@end
