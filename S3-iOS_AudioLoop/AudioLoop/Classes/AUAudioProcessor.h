//
//  AUAudioProcessor.h
//  AudioLoop
//
//  Created by Thomas Hézard on 2019/02/02.
//  Copyright © 2019 THZ. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

// AUAudioProcessor works only at 48kHz

@interface AUAudioProcessor : AUAudioUnit

+ (void) registerAudioUnitAndBuildDescription:(AudioComponentDescription*)description;

- (void) setParam:(int)paramID value:(float)value;

- (float) getParam:(int)paramID;

@end

NS_ASSUME_NONNULL_END
