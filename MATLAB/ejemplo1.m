     [inputs,targets] = simplefitdata;
     net = newff(inputs,targets,20);
     net = train(net,inputs,targets);
     outputs = net(inputs);
     errors = outputs - targets;
     perf = perform(net,outputs,targets)