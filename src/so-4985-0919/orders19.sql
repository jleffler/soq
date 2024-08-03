
create table zipcode (
  zip   integer{5} primary key,
  city  varchar(30),
  State varchar(20));


create table employee (
  eno       varchar(10) primary key,
  ename     varchar(30),
  zip       integer{5} references zipcode(zip),
  hire_date date);



create table book (
  bno       integer{5} primary key,
  bname     varchar(30),
  qoh       integer{5} not null,
  price     dec(6,2) not null);


create table customer (
  cno       integer{5} primary key,
  cname     varchar(30),
  street    varchar(30),
  zip       integer{5}  references zipcode(zip),
  phone     char(12));



create table salesOrder (
  ono       integer{5}  primary key,
  cno       integer{5}  references customer(cno),
  eno       varchar(10)  references employee(eno),
  received  date,
  shipped   date
);



create table orderLine (
  ono       integer{5}  references salesOrder(ono),
  bno       integer{5}  references book(bno),
  quantity  integer{10} not null,
  primary key (ono, bno));




insert into zipcode values (98225, 'Bellingham', 'WA');
insert into zipcode values (95388, 'Winton', 'CA');
insert into zipcode values (44242, 'Stow', 'OH');
insert into zipcode values (61536, 'Hanna city', 'IL');
insert into zipcode values (01254, 'Richmond', 'MA');
insert into zipcode values (95124, 'San Jose', 'CA');
insert into zipcode values (95382, 'Turlock', 'CA');
insert into zipcode values (95380, 'Turlock', 'CA');
insert into zipcode values (98102, 'Seattle', 'WA');



insert into employee values ('P0239401', 'Jones Hoffer',98225, '2000-12-12');
insert into employee values ('P0239402', 'Jeffrey Prescott',95388, '2016-11-07');
insert into employee values ('P0239403', 'Fred NcFaddeb',95124, '2008-09-01');
insert into employee values ('P0239404', 'Karen Ives',98102, '2014-05-21');


insert into book values (10501, 'Forensic Accounting',200, 229.99);
insert into book values (10502, 'SAP Business One',159, 149.99);
insert into book values (10503, 'Fraud Cases',190, 179.99);
insert into book values (10504, 'CPA Review',65, 279.99);
insert into book values (10605, 'Quickbooks for Business',322, 59.99);
insert into book values (10704, 'Financial Accounting',129, 164.99);
insert into book values (10879, 'Managerial Accounting',155, 114.99);
insert into book values (10933, 'Cost Accounting',122, 219.99);
insert into book values (10948, 'Intermediate Accounting',123, 164.99);
insert into book values (10965, 'Accounting Information Systems',211, 259.99);
insert into book values (10988, 'XBRL in Nutshell',124, 109.99);


insert into customer values (23511, 'Michelle Kuan', '123 Main St.',98225, '360-636-5555');
insert into customer values (23512, 'George Myer', '237 Ash Ave.',95124, '312-678-5555');
insert into customer values (23513, 'Richard Gold', '111 Inwood St.',95124, '312-883-7337');
insert into customer values (23514, 'Robert Smith', '54 Gate Dr.',95388, '206-832-1221');
insert into customer values (23515, 'Christopher David', '777 Loto St.',98225, '360-458-9878');
insert into customer values (23516, 'Adam Beethoven', '234 Park Rd.',95380, '209-546-7299');
insert into customer values (23517, 'Ludwig Bach', '5790 Walnut St.',95382, '209-638-2712');
insert into customer values (23518, 'Kathleen Pedersen', '1233 Federal Ave E', 98102, '360-573-7239');


insert into salesOrder values (1020, 23511, 'P0239403', '2018-01-13', '2018-01-15');
insert into salesOrder values (1021, 23513, 'P0239401', '2018-01-13', '2018-01-16');
insert into salesOrder values (1022, 23513, 'P0239402', '2018-01-15', '2018-01-17');
insert into salesOrder values (1023, 23512, 'P0239403', '2018-01-16', '2018-01-18');
insert into salesOrder values (1024, 23511, 'P0239402', '2018-01-18', '2018-01-20');
insert into salesOrder values (1025, 23511, 'P0239403', '2018-01-29', '2017-01-31');
insert into salesOrder values (1026, 23512, 'P0239404', '2018-01-30', '2018-01-31');
insert into salesOrder values (1027, 23512, 'P0239402', '2018-01-30', '2018-01-31');
insert into salesOrder values (1028, 23512, 'P0239404', '2018-01-30', '2018-01-31');
insert into salesOrder (ONO, CNO, ENO, RECEIVED) values (1029, 23513, 'P0239402', '2018-01-31');
insert into salesOrder (ONO, CNO, ENO, RECEIVED) values (1030, 23511, 'P0239401', '2018-01-31');



insert into orderLine values (1020, 10501,7);
insert into orderLine values (1020, 10502,15);
insert into orderLine values (1020, 10504,3);
insert into orderLine values (1020, 10503,6);
insert into orderLine values (1021, 10605,4);
insert into orderLine values (1022, 10605,2);
insert into orderLine values (1022, 10704,4);
insert into orderLine values (1023, 10879,4);
insert into orderLine values (1023, 10988,19);
insert into orderLine values (1024, 10502,7);
insert into orderLine values (1024, 10988,2);
insert into orderLine values (1025, 10502,4);
insert into orderLine values (1025, 10988,3);
insert into orderLine values (1025, 10948,2);
insert into orderLine values (1026, 10965,15);
insert into orderLine values (1026, 10933,5);
insert into orderLine values (1027, 10933,21);
insert into orderLine values (1028, 10933,9);
insert into orderLine values (1028, 10965,11);
insert into orderLine values (1029, 10933,4);
insert into orderLine values (1029, 10965,10);
insert into orderLine values (1029, 10988,3);
