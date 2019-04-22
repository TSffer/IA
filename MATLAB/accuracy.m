function return_value = accuracy(net,input,target)
output=sim(net,input);
correct=0;
for i=1:length(output)
 if ((target(i)==1) & (output(i)>=0.5))
   correct=correct+1;
  elseif ((target(i)==0) & (output(i)<0.5))
   correct=correct+1;
 end;    
end;
return_value = correct./length(output); 