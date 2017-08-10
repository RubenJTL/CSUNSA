load num1.dat;
cluster=num1(1,1);
load puntos1.dat;
x=puntos1(:,1);
y=puntos1(:,2);
c=puntos1(:,3);
hold on;
for i = 1:cluster
  if(c(i)==0)
    plot(x(i),y(i),'r');
  elseif(c(i)==1)
    plot(x(i),y(i),'b');
  elseif(c(i)==2)
    plot(x(i),y(i),'g');  
  elseif(c(i)==3)
    plot(x(i),y(i),'y');  
  elseif(c(i)==4)
    plot(x(i),y(i),'m');  
  elseif(c(i)==5)
    plot(x(i),y(i),'c');    
  elseif(c(i)==6)
    plot(x(i),y(i),'k');  
  endif
endfor

pause(2);
