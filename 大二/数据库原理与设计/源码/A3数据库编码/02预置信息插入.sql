use bit_pc

insert into user_type values(1,'����Ա')
insert into user_type values(2,'��ͨ�û�')
select id as '�û����ͱ�ʶ���', typename as '�û�����������' from user_type

insert into users values(1520511410,1,'������','1520511410','2001.6.23')
insert into users values(1523006999,2,'��Y','tree1062','2001.1.29')
insert into users values(1213389134,2,'Ͱͬ','tongtong!','2002.6.1')
select id as '�û��˺�',typeid as '�û����ͱ�ʶ���',username as '�û�����',pw as '����', birthday as '�û���������' from users order by users.id

insert into shows values(2,'2021.7.4','����',88,'�����ĺű���',100)
insert into shows values(3,'2021.7.4','����',88,'�����ĺŹ���',100)
insert into shows values(4,'2021.7.4','�Ͼ�',88,'�����ĺ��Ͼ�',100)
insert into shows values(5,'2021.6.23','����',66,'���¶�ʮ������',100)
insert into shows values(1,'2021.5.5','����',55,'������ű���',100)
insert into shows values(6,'2021.5.5','����',55,'������Ź���',100)
insert into shows values(7,'2021.5.7','����',57,'�����ߺű���',100)
select id as '�ݳ����α�ʶid', showtime as '�ݳ�ʱ��',place as '�ݳ��ص�',title as '�ݳ�����',price as '�ݳ�Ʊ��', ticket as '�ݳ�Ʊ����' from shows
select * from shows

insert into performer values(1,'�Ӳ�','1989.2.22')
insert into performer values(2,'����','1996.1.22')
insert into performer values(3,'House','1992.3.20')
insert into performer values(4,'�����','1988.8.26')
insert into performer values(5,'CL','1985.5.8')
insert into performer values(6,'˼��','1986.4.30')
insert into performer values(7,'������','2000.1.1')
select id as '�ݳ���Ա���', pname as '�ݳ���Ա����', birthday as '��������' from performer

insert into who_onshow values(5,1,1)
insert into who_onshow values(5,2,2)
insert into who_onshow values(5,3,3)
insert into who_onshow values(5,4,4)
insert into who_onshow values(5,5,5)
insert into who_onshow values(5,6,6)
insert into who_onshow values(5,7,7)
insert into who_onshow values(1,2,1)
insert into who_onshow values(2,4,1)
insert into who_onshow values(2,5,2)
insert into who_onshow values(3,6,1)
insert into who_onshow values(3,1,2)
insert into who_onshow values(4,2,1)
insert into who_onshow values(4,7,2)
insert into who_onshow values(6,7,1)
insert into who_onshow values(6,1,2)
insert into who_onshow values(6,4,3)
insert into who_onshow values(7,1,2)
insert into who_onshow values(7,5,1)
insert into who_onshow values(7,7,3)
select pid as '�ݳ����α�ʶid', onid as '�ݳ���Ա���',onsequence as '�ϳ�˳��' from who_onshow

insert into sells values(1523006999,2,2,1)
insert into sells values(1523006999,1,10,1)
insert into sells values(1213389134,6,10,1)
insert into sells values(1213389134,6,10,0)
insert into sells values(1213389134,5,1,1)
select aid as "��Ʊ�û��˺�", pid as "�ݳ����α�ʶid",number as '��Ʊ����',buystatus as '��Ʊ�Ƿ�ɹ�' from sells

