//
//  AudioController.m
//  AudioLoop
//
//  Created by Thomas Hézard on 2019/02/02.
//  Copyright © 2019 THZ. All rights reserved.
//


#import "AudioController.h"
#import "AUAudioProcessor.h"


@interface AudioController()

@property (nonatomic, assign)   AudioComponentDescription   auDescription;

@property (nonatomic, strong)   AVAudioFormat               *monoFormat;

@property (nonatomic, strong)   AUAudioProcessor            *auProcessor;
@property (nonatomic, strong)   AVAudioNode                 *avProcessor;

@property (nonatomic, strong)   AVAudioEngine               *engine;
@property (nonatomic, strong)   AVAudioMixerNode            *inputMixer;

@property (nonatomic, assign)   BOOL                        isEngineStarted; // Engine is expecting to run

@end



@implementation AudioController

- (instancetype) init {
    
    self = [super init];
    if (self) {
        
        [AUAudioProcessor registerAudioUnitAndBuildDescription:&_auDescription];
        
        [AVAudioUnit instantiateWithComponentDescription:self.auDescription options:0 completionHandler:^(__kindof AVAudioUnit * _Nullable audioUnit, NSError * _Nullable error) {
            if (audioUnit == nil || error != nil) {
                return;
            }
            self.avProcessor = audioUnit;
            self.auProcessor = (AUAudioProcessor*)audioUnit.AUAudioUnit;
        }];
        
        float defaultSampleRate = 48000.0;
        
        self.monoFormat = [[AVAudioFormat alloc] initWithCommonFormat:AVAudioPCMFormatFloat32 sampleRate:defaultSampleRate channels:1 interleaved:NO];
        
        [self setupAudioSession];
        
        self.engine = [[AVAudioEngine alloc] init];
        self.inputMixer = [[AVAudioMixerNode alloc] init];
        
        [self attachAndConnectAllNodes];
        
        [self registerForNotifications];
        
    }
    return self;
}


- (void)setupAudioSession {
    
    NSError *error = nil;
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayAndRecord withOptions:0 error:&error];
    if (error) {
        return;
    }
    [[AVAudioSession sharedInstance] setPreferredSampleRate:self.monoFormat.sampleRate error:&error];
    if (error) {
        return;
    }
    [[AVAudioSession sharedInstance] setPreferredIOBufferDuration:0.005f error:&error];
    if (error) {
        return;
    }
}


- (void)registerForNotifications {
    
    NSNotificationCenter* notificationCenter = [NSNotificationCenter defaultCenter];
    [notificationCenter addObserver:self selector:@selector(handleInterruption:) name:AVAudioSessionInterruptionNotification object:[AVAudioSession sharedInstance]];
    [notificationCenter addObserver:self selector:@selector(handleMediaServicesReset:) name:AVAudioSessionMediaServicesWereResetNotification object:[AVAudioSession sharedInstance]];
    [notificationCenter addObserver:self selector:@selector(handleConfigurationChange:) name:AVAudioEngineConfigurationChangeNotification object:self.engine];
}


- (void)unregisterNotifications {
    
    NSNotificationCenter* notificationCenter = [NSNotificationCenter defaultCenter];
    [notificationCenter removeObserver:self name:AVAudioSessionInterruptionNotification object:[AVAudioSession sharedInstance]];
    [notificationCenter removeObserver:self name:AVAudioSessionMediaServicesWereResetNotification object:[AVAudioSession sharedInstance]];
    [notificationCenter removeObserver:self name:AVAudioEngineConfigurationChangeNotification object:self.engine];
}


- (void)handleInterruption:(NSNotification *)notification {
    
    @synchronized (self) {
        
        UInt8 theInterruptionType = [[notification.userInfo valueForKey:AVAudioSessionInterruptionTypeKey] intValue];
        
        NSString *interruptString = theInterruptionType == AVAudioSessionInterruptionTypeBegan ? @"Begin Interruption" : @"End Interruption";
        NSString *message = [NSString stringWithFormat:@"[AudioController] ** SYSTEM EVENT ** %@ ", interruptString];
        NSLog(@"%@", message);
        
        if (theInterruptionType == AVAudioSessionInterruptionTypeBegan) {
            [self internalStopAudioRendering];
        }
        else if (theInterruptionType == AVAudioSessionInterruptionTypeEnded) {
            // make sure to activate the session
            if (self.isEngineStarted) {
                [self internalStartAudioRendering];
            }
        }
    }
}


- (void)handleMediaServicesReset:(NSNotification *)notification {
    // if we've received this notification, the media server has been reset
    // re-wire all the connections and start the engine
    
    @synchronized (self) {
        
        BOOL wasRendering = self.engine.running;
        if (wasRendering) {
            [self.engine stop];
            [self.engine reset];
        }
        
        [self unregisterNotifications];
        
        [self detachAllNodes];
        
        self.engine = nil;
        
        [self setupAudioSession];
        
        self.engine = [[AVAudioEngine alloc] init];
        
        [self attachAndConnectAllNodes];
        
        [self registerForNotifications];
        
        if (self.isEngineStarted) {
            [self internalStartAudioRendering];
        }
    }
}


- (void) handleConfigurationChange:(NSNotification *)notification {
    
    @synchronized (self) {
        if (self.isEngineStarted) {
            [self internalStartAudioRendering];
        }
    }
}


- (void) attachAndConnectAllNodes {
    
    [self.engine attachNode:self.inputMixer];
    [self.engine attachNode:self.avProcessor];
    
    [self.engine connect:self.engine.inputNode to:self.inputMixer format:[self.engine.inputNode inputFormatForBus:0]];
    [self.engine connect:self.inputMixer to:self.avProcessor format:self.monoFormat];
    
    [self.engine connect:self.avProcessor to:self.engine.mainMixerNode format:self.monoFormat];
}


- (void) detachAllNodes {
    
    [self.engine detachNode:self.inputMixer];
    [self.engine detachNode:self.avProcessor];
}


- (void) startAudioRendering {
    
    @synchronized (self) {
        if (self.engine) {
            [self internalStartAudioRendering];
        }
        self.isEngineStarted = YES;
    }
}


- (void) internalStartAudioRendering {
    
    // Set Audio Session active
    NSError *error = nil;
    [[AVAudioSession sharedInstance] setActive:YES error:&error];
    
    // Check if AudioEngine is already running
    if (self.engine.isRunning) {
        return;
    }
    
    // Reset Audio Engine
    [self.engine reset];
    
    // Start Audio Engine
    [self.engine startAndReturnError:&error];
}


- (void) stopAudioRendering {
    
    @synchronized (self) {
        if (self.engine) {
            [self internalStopAudioRendering];
        }
        self.isEngineStarted = NO;
    }
}


- (void) internalStopAudioRendering {
    
    if (self.engine.isRunning) {
        [self.engine stop];
    }
}


@end
