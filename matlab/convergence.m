
syms a b c x y

r = 1;
s = 100;
l = 0.001;
q = 0.9;
p = 1;
f1 = symfun(-r*a + sqrt((a-b)*(a-b))*x/q,[a,b,c,x,y]);
f2 = symfun(s - sqrt((a-b)*(a-b))*x/q - sqrt((b-c)*(b-c))*y/p,[a,b,c,x,y]);
f3 = symfun(-r*c + sqrt((c-b)*(c-b))*y/p,[a,b,c,x,y]);
f4 = symfun((sqrt((a-b)*(a-b))/q - l)*x,[a,b,c,x,y]);
f5 = symfun((sqrt((c-b)*(c-b))/p - l)*y,[a,b,c,x,y]);


j = jacobian([f1,f2,f3,f4,f5],[a,b,c,x,y])

z = solve(f1==0, f2==0, f3==0, f4==0, f5==0, a,b,c,x,y);
eigs = zeros(5,length(z.a));
sols = zeros(5,length(z.a));
for i = 1:length(z.a)
a = double(z.a(i)); b = double(z.b(i)); c = double(z.c(i)); x = double(z.x(i)); y = double(z.y(i));
sols(:,i) = [a;b;c;x;y];
eigs(:,i) = eig(eval(j));
end

