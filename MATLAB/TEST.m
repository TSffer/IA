bcdata=csvread('wdbc.csv',0,1);
size(bcdata)
bcdata=bcdata';
size(bcdata)
%temp_target=bcdata(1,:);
target=bcdata(1,:);
indata=bcdata(2:31,:);

input_ranges=minmax(indata);
net=newff(input_ranges,[10 1],{'tansig','logsig'},'trainlm'); 

training_in = indata(:,1:2:length(indata));
testset.P = indata(:,2:2:length(indata));

training_target = target(1:2:length(target));
testset.T = target(2:2:length(target));

net.trainParam.show=1;
net=train(net,training_in,training_target,[],[],testset);

porc_err_ent = 100*(1-accuracy(net,training_in,training_target))
porc_err_valida = 100*(1-accuracy(net,testset.P,testset.T))
porc_err_todo = 100*(1-accuracy(net,indata,target))