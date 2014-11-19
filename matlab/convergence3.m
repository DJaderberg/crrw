reset(symengine)
clear
syms a b c x y z

r = 100;
s = 100;
l = 0.3;
l1 = 1;
l2 = 1;
l3 = 1;
f1 = symfun(s - (a-b)*x/l1 - (a-c)*z/l3,[a,b,c,x,y,z]); %N_a
f2 = symfun(-(b-a)*x/l1 - (b-c)*y/l2,[a,b,c,x,y,z]); %N_b
f3 = symfun(-r - (c-a)*z/l3 - (c-b)*y/l2,[a,b,c,x,y,z]); %N_c
f4 = symfun((sqrt((a-b)*(a-b))/l1 - l)*x,[a,b,c,x,y,z]); %D_ab
f5 = symfun((sqrt((a-c)*(a-c))/l3 - l)*z,[a,b,c,x,y,z]); %D_ac
f6 = symfun((sqrt((b-c)*(b-c))/l2 - l)*y,[a,b,c,x,y,z]); %D_bc


j = jacobian([f1,f2,f3,f4,f5,f6],[a,b,c,x,y,z])

w = solve([f1==0, f2==0, f3==0, f4==0, f5==0, f6==0], [a,b,c,x,y,z]);

for i = 1:length(w.a)
a = double(w.a(i)); b = double(w.b(i)); c = double(w.c(i)); x = double(w.x(i)); y = double(w.y(i)); z = double(w.y(i));
sols(:,i) = [a;b;c;x;y];
eval(j)
%eigs(:,i) = eig(eval(j));
end
