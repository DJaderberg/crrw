data = csvread('../data/sizeup.txt', 1, 0)
nThreads = 1:1:16;

unique_data = [];
nodes = 10000;
insert = 1e30;
threads = 1;
for i = 1:length(data)
    row = data(i,:);
    if row(1) == threads
        if row(2) < insert
            insert = row(2);
        end
    else
        unique_data = [unique_data;[threads, insert, nodes]];
        threads = row(1);
        insert = row(2);
    end
end
unique_data = [unique_data;[threads, insert, nodes]];
for i = 1:size(unique_data,1)
    sizeups(1,i) = unique_data(i,2)/unique_data(1,2);
end

%plot(unique_data(:,1), sizeups)

%--------full screen-----------------
fig1 = figure;
set(fig1,'units','normalized','outerposition',[0 0 1 1]);
%----------------------------------------
versions = {'Pragma schedule - Static', 'Pragma task', 'Bin-Pack', 'Run time system'};

col={'.--b','.--r','.--g','.--m','.--c','.--y','.--k'};

%name = {'problem size: '};
%str=sprintf('%d x %d matrices',sizes(i),sizes(i));
plot(unique_data(:,1), sizeups,col{2},'markersize',30,'linewidth',2);
%s(i)=strcat(name,str);

legend('Sizeup', 'Location', 'NorthWest');
set(gca,'XTick',nThreads);
set(gca,'FontSize',23) %set scale fontsize
title('Sizeup')
xlabel('# of threads')
ylabel('Sizeup [ ]')
set(gca,'XTick',nThreads);
ylim([0 nThreads(end)/2])