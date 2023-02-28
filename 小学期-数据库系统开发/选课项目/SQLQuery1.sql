


USE  LessonChoice
--table!!!!!!!
create table Student (
ID int NOT NULL primary key,
[name] varchar(255),
gender varchar(10),
class int NOT NULL
)

create table Teacher (
ID int NOT NULL primary key,
[name] varchar(255) NOT NULL
)

create table Lessons ( 
[name] varchar(1024) NOT NULL primary key,
credit float NOT NULL,
teacherID int NOT NULL,
[time] varchar(1024)
)

alter table Lessons
   add constraint FK_Lessons_Teacher foreign key (teacherID)
      references Teacher (ID)
go

create table TakeLesson ( 
StudentID int NOT NULL,
Lessonname varchar(1024) NOT NULL
)

alter table TakeLesson
   add constraint FK_TakeLesson_Lesson foreign key (Lessonname)
      references Lessons ([name])
go

alter table TakeLesson
   add constraint FK_TakeLesson_Student foreign key (StudentID)
      references Student (ID)
go

create table TempTakeLesson ( 
StudentID int NOT NULL,
Lessonname varchar(1024) NOT NULL
)

alter table TempTakeLesson
   add constraint FK_TempTakeLesson_Lesson foreign key (Lessonname)
      references Lessons ([name])
go

alter table TempTakeLesson
   add constraint FK_TempTakeLesson_Student foreign key (StudentID)
      references Student (ID)
go


--insert!!!!!!!!!!
insert into Student values(1120190699,' ������','female',30141901);
insert into Student values(1120190219,' ����','male',30141901);
insert into Student values(1120191034,' ����','male',30141901);
insert into Student values(1120190124,' С��','female',30141901);
insert into Student values(1120191535,' С��','male',30141901);
insert into Student values(1120195272,' ����','male',30141901);
insert into Student values(1120191345,' ��paul','male',30141901);
insert into Student values(1120192521,' Ͱͬ','female',30141901);
insert into Student values(1120190629,' ʷ��ķ','male',30141901);
insert into Student values(1120190612,' ѼѼ','male',30141901);
insert into Student values(1120190214,' ���ָ�ҰѼ','male',30141901);
select * from Student



insert into Teacher values(331201,'�ʡ');
insert into Teacher values(331202,'�����');
insert into Teacher values(331203,'������');
insert into Teacher values(331204,'������');
insert into Teacher values(331205,'��');
insert into Teacher values(331206,'������');
insert into Teacher values(331207,'��Ө');
insert into Teacher values(331208,'����');
insert into Teacher values(331209,'��Ծ');
insert into Teacher values(331210,'κʤ��');
insert into Teacher values(331211,'����');
insert into Teacher values(331212,'����');
insert into Teacher values(331213,'����');
insert into Teacher values(331214,'������');
insert into Teacher values(331215,'����ʩ');
select * from Teacher



insert into Lessons values('���ݿ⿪�����',1.5,331212,'ÿ��һ2-5��');
insert into Lessons values('֪ʶ����',2,331201,'ÿ����2-5��');
insert into Lessons values('����ѧϰ����',2,331204,'ÿ��һ6-7��');
insert into Lessons values('�˹����ܻ���',2.5,331211,'ÿ�ܶ�3-5��');
insert into Lessons values('���Ż�����',2,331202,'ÿ����2-5��');
insert into Lessons values('�����ѧ',2,331208,'ÿ����9-10��');
insert into Lessons values('Linuxϵͳ���',2,331207,'ÿ��һ11-13��');
insert into Lessons values('������¼���ר��',2,331206,'ÿ�ܶ�6-7��');
insert into Lessons values('����ѧ����',2.5,331212,'ÿ����6-7��');
insert into Lessons values('�����ͼ��ѧ',2.5,331209,'ÿ����6-7��');
insert into Lessons values('Ƕ��ʽ����ϵͳ',2.5,331205,'ÿ����6-8��');
insert into Lessons values('�����������Matlab',2,331203,'ÿ��һ8-9��');
insert into Lessons values('����ͼ����',2.5,331213,'ÿ����1-2��');
insert into Lessons values('�ִ��˻�����',2,331214,'ÿ�ܶ�1-2��');
select * from Lessons

insert into TakeLesson values(1120190699,'�����������Matlab');
insert into TakeLesson values(1120190699,'�ִ��˻�����');
insert into TakeLesson values(1120190214,'�ִ��˻�����');
insert into TakeLesson values(1120190214,'����ͼ����');

--procedure!!!!!!!!!!!
IF EXISTS (SELECT name FROM sysobjects 
         WHERE name = 'SelectTakenLesson' AND type = 'P')
   DROP PROCEDURE SelectTakenLesson
GO
CREATE PROCEDURE SelectTakenLesson
	@n int
AS
BEGIN
	SELECT Lessons.[name] as '�γ�����', Lessons.credit as 'ѧ��', Teacher.[name] as '�ڿν�ʦ', Lessons.[time] as '�Ͽ�ʱ��'
	FROM Lessons INNER JOIN Teacher 
		ON Lessons.teacherID = Teacher.ID INNER JOIN TakeLesson
		ON TakeLesson.Lessonname = Lessons.[name] INNER JOIN Student
		ON TakeLesson.StudentID = Student.ID
	WHERE Student.ID = @n
END
GO

execute SelectTakenLesson 1120190214

IF EXISTS (SELECT name FROM sysobjects 
         WHERE name = 'SelectUntakeLesson' AND type = 'P')
   DROP PROCEDURE SelectUntakeLesson
GO
CREATE PROCEDURE SelectUntakeLesson
	@n int
AS
BEGIN
	SELECT Lessons.[name] as '�γ�����', Lessons.credit as 'ѧ��', Teacher.[name] as '�ڿν�ʦ', Lessons.[time] as '�Ͽ�ʱ��'
	FROM Lessons INNER JOIN Teacher 
		ON Lessons.teacherID = Teacher.ID 
	WHERE Lessons.[name] NOT IN (SELECT Lessonname FROM TakeLesson WHERE StudentID = @n)
END
GO

execute SelectUntakeLesson 1120190699


