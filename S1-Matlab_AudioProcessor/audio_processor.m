%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Offline Audio Processor %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%% Parameters

% This must be an audio file readable by Matlab audioread function
fileName = 'Marimba.wav';



%% Read input file

[inputData, sampleRate] = audioread(fileName);
inputData = mean(inputData,2); % downmix to mono
inputTime = (0:length(inputData)-1)/sampleRate;

figure(1);
plot(inputTime, inputData);
grid on;
title('Input audio data');
xlabel('time (seconds)');
ylabel('amplitude');

soundsc(inputData,sampleRate);
pause(length(inputData)/sampleRate);



%% Audio data process

outputData = zeros(size(inputData));

%%%%%%%%%%%%%%%%%%%%%%%%%
% PROCESSING COMES HERE %
%%%%%%%%%%%%%%%%%%%%%%%%%

outputData = inputData;

%%%%%%%%%%%%%%%%%%%%%%%%%



%% Save output

audiowrite('output.wav',outputData, sampleRate);
soundsc(outputData,sampleRate);
figure(2);
outputTime = (0:length(outputData)-1)/sampleRate;
plot(outputTime, outputData);
grid on;
title('Output audio data');
xlabel('time (seconds)');
ylabel('amplitude');