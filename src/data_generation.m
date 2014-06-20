% Generate data
% Number of records to generate
NCOL = 9;
SIZE = 100*1024*1024;

NLINES = SIZE/NCOL/8;
NLINES = ceil(NLINES);

A = zeros(NLINES,NCOL);

for i=1:NLINES
    A(i,:) = rand(1,NCOL);
end

csvwrite('100MB',A);