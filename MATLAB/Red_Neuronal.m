bcdata = csvread('wdbc.csv',0,1);
size(bcdata);
bcdata = bcdata';
size(bcdata);

target = bcdata(1,:);
indata = bcdata(2:31,:);

input_ranges = minmax(indata);

net=newff(input_ranges,[10 1],{'tansig','logsig'},'trainlm'); 

training_in = indata(:,1:2:length(indata));
training_target = target(1:2:length(target));
testset.P = indata(:,2:2:length(indata));
testset.T = target(2:2:length(target));

net.trainParam.show=1;
net=train(net,training_in,training_target,[],[],testset); 
 