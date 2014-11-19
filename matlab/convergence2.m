reset(symengine)
clear
syms a b x y

r = 1;
s = 100;
l = 0.3;
q = 2;
p = 1.7;
%f1 = symfun(s - sqrt((a-b)*(a-b))*(x/q + y/p),[a,b,x,y]);
%f2 = symfun(-r*b + sqrt((a-b)*(a-b))*(x/q + y/p),[a,b,x,y]);
%f3 = symfun((sqrt((a-b)*(a-b))/q - l)*x,[a,b,x,y]);
%f4 = symfun((sqrt((a-b)*(a-b))/p - l)*y,[a,b,x,y]);
f1 = symfun(s - (a-b)*(x/q + y/p),[a,b,x,y]);
f2 = symfun(-r*b + (a-b)*(x/q + y/p),[a,b,x,y]);
f3 = symfun(((a-b)/q - l)*x,[a,b,x,y]);
f4 = symfun(((a-b)/p - l)*y,[a,b,x,y]);


j = jacobian([f1,f2,f3,f4],[a,b,x,y])

z = solve([f1==0, f2==0, f3==0, f4==0], [a,b,x,y]);

for i = 1:length(z.a)
a = double(z.a(i)); b = double(z.b(i)); x = double(z.x(i)); y = double(z.y(i));
sols(:,i) = [a;b;x;y];
eigs(:,i) = eig(eval(j));
end
