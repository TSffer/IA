 [inputs,targets] = simplefit_dataset;
 net = newff(inputs,targets,[20 1 1],{'linear'});
 net = train(net,inputs,targets);
 outputs = net(inputs);
 errors = outputs - targets;
 perf = perform(net,outputs,targets)
 
 %varianza y error
%crossvalidation