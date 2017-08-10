load num1.dat;
cluster=num1(1,1);
load puntos1.dat;

x=puntos1(:,1);
y=puntos1(:,2);
z=puntos1(:,3);
c=puntos1(:,5);
plot3(x,y,z,"*");
hold on;
for i = 1:cluster
  if(c(i)==0)
    plot3(x(i),y(i),z(i),'r*');
  elseif(c(i)==1)
    plot3(x(i),y(i),z(i),'b*');
  elseif(c(i)==2)
    plot3(x(i),y(i),z(i),'g*');  
  elseif(c(i)==3)
    plot3(x(i),y(i),z(i),'y*');  
  elseif(c(i)==4)
    plot3(x(i),y(i),z(i),'m*');  
  elseif(c(i)==5)
    plot3(x(i),y(i),z(i),'c*');    
  elseif(c(i)==6)
    plot3(x(i),y(i),z(i),'k*');  
  endif
endfor

pause(2);
