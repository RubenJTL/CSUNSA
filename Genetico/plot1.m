tx = ty = linspace (0, 10000, 20)';
[xx, yy] = meshgrid (tx, ty);
r = exp(-(((xx-4096).^2 + (yy-4096).^2)./(2*(1500^2))));
tz = (1/(sqrt(2*pi)*1500^2))*r;
mesh (tx, ty, tz);hold on;
xlabel ("tx");
ylabel ("ty");
zlabel ("tz");
title ("3-D Sombrero plot");


load puntos.dat;
plot3(puntos(:,1),puntos(:,2),puntos(:,3),"*");
pause(20);

