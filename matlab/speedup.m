%cat data/speedup.txt | grep 10k | awk '{print $1, $2, $3}' > data/speedup_10k.txt
data = csvread('../data/speedup_10k.txt');

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
    speedups(1,i) = unique_data(1,2)/unique_data(i,2);
end

plot(unique_data(:,1), speedups)