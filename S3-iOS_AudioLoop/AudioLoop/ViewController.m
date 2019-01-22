//
//  ViewController.m
//  AudioLoop
//
//  Created by Thomas Hézard on 2019/02/02.
//  Copyright © 2019 THZ. All rights reserved.
//

#import "ViewController.h"
#import "AudioController.h"

@interface ViewController ()

@property (nonatomic, strong)   AudioController*    audioController;
@property (weak, nonatomic) IBOutlet UISlider *slider0;
@property (weak, nonatomic) IBOutlet UISlider *slider1;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    if (self.audioController == nil) {
        self.audioController = [[AudioController alloc] init];
    }
    
    [self.audioController startAudioRendering];
    self.slider0.value = [self.audioController.auProcessor getParam:0];
}

- (IBAction)onSlider0Chnaged:(UISlider *)sender {
    [self.audioController.auProcessor setParam:0 value:sender.value];
    sender.value = [self.audioController.auProcessor getParam:0];
}

@end
