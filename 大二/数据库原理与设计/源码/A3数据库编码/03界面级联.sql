use bit_pc

--��������ʾ������
alter table who_onshow add constraint onid_performer_id foreign key(onid) references performer(id) on update cascade on delete cascade

ALTER TABLE [dbo].[who_onshow]  WITH CHECK ADD FOREIGN KEY([pid])
REFERENCES [dbo].[shows] ([id])
ON UPDATE CASCADE
ON DELETE CASCADE

ALTER TABLE [dbo].[users]  WITH CHECK ADD FOREIGN KEY([typeid])
REFERENCES [dbo].[user_type] ([id])
ON UPDATE CASCADE
ON DELETE CASCADE

alter table sells add constraint onid_sells_aid foreign key(aid) references users(id) on update cascade on delete cascade

alter table sells add constraint onid_sells_pid foreign key(pid) references shows(id) on update cascade on delete cascade
--�����޸�shows�е�id=1��id=10

update shows set id=10 where id=1
select id as '�ݳ����α�ʶid', showtime as '�ݳ�ʱ��',place as '�ݳ��ص�',title as '�ݳ�����',price as '�ݳ�Ʊ��', ticket as '�ݳ�Ʊ����' from shows
select aid as '��Ʊ�û��˺�', pid as '�ݳ����α�ʶid',number as '��Ʊ����',buystatus as '��Ʊ�Ƿ�ɹ�(1�ɹ���0ʧ��)' from sells

--���ݳ���Ա��Ϣ����ɾ��7����Ա������
delete from performer where id=7
select id as '�ݳ���Ա���', pname as '�ݳ���Ա����', birthday as '��������' from performer
select pid as '�ݳ����α�ʶid', onid as '�ݳ���Ա���',pname as '�ݳ���Ա����',onsequence as '�ϳ�˳��'
from who_onshow
left join performer on performer.id=onid
where pid>=4

update shows set id=1 where id=10