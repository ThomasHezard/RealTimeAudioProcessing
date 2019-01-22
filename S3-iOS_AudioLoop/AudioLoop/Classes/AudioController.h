//
//  AudioController.h
//  AudioLoop
//
//  Created by Thomas Hézard on 2019/02/02.
//  Copyright © 2019 THZ. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AUAudioProcessor.h"

NS_ASSUME_NONNULL_BEGIN

@interface AudioController : NSObject

- (void) startAudioRendering;

- (void) stopAudioRendering;

@property (nonatomic, strong, readonly) AUAudioProcessor    *auProcessor;

@end

NS_ASSUME_NONNULL_END
