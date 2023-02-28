use bit_pc

--����Ա��ѯ��Ʊ����Ĵ洢����
go
create procedure select_sells
@t date
as
begin
	delete from sells where number<=0
	delete from sells where buystatus=0  --initialization
	select
	"�ݳ��ص�"=place,
	"�ݳ�ʱ��"=showtime,
	"�ݳ�Ʊ��"=price,
	"��Ʊ��"=ticket,
	"��Ʊ"=case when buystatus=1 then ticket-sum(number) else ticket end,
	"�ݳ�����"=title,
	"��ʶid"=id
	from shows
	left join sells on pid=id
	group by ticket,place,showtime,title,price,buystatus,id
	having showtime>@t
	order by showtime
end

exec select_sells '2021-6-1'

--��ѯ�ݳ���Ϣ�Ĵ洢����
go
create procedure show_ifo
@t int
as begin
	select
	"�ݳ��ص�"=place,
	"�ݳ�ʱ��"=showtime,
	"�ݳ�Ʊ��"=price,
	"��Ʊ��"=ticket,
	"��Ʊ"=case when buystatus=1 then ticket-sum(number) else ticket end,
	"�ݳ�����"=title
	from shows
	left join sells on pid=id
	group by ticket,place,showtime,title,price,buystatus,id
	having id=@t
end

exec show_ifo 1

--׼ȷ��ѯ���յĴ洢����
go
create procedure select_birthday
@t int
as
begin
select pname as "��Ա����",birthday as "����",
"����"=
(
	case when (
	(datepart(m,getdate())>datepart(m,birthday))
	or(
		(datepart(m,getdate())=datepart(m,birthday))
		and
		(datepart(d,getdate())>datepart(d,birthday))
		)
	)
	then (year(getdate())-year(birthday))
	else (year(getdate())-year(birthday)-1)
	end
),id as "��ʶid"
from performer
where datepart(m,birthday)=@t
end

go
create procedure select_birthday_null
as
begin
select pname as "��Ա����",birthday as "����",
"����"=
(
	case when (
	(datepart(m,getdate())>datepart(m,birthday))
	or(
		(datepart(m,getdate())=datepart(m,birthday))
		and
		(datepart(d,getdate())>datepart(d,birthday))
		)
	)
	then (year(getdate())-year(birthday))
	else (year(getdate())-year(birthday)-1)
	end
),id as "��ʶid"
from performer
end

exec select_birthday 8

go
create procedure arrange_se
@t int
as begin
select "�ϳ�˳��"=onsequence,
"�ݳ�ʱ��"=showtime,
"��Ա����"=pname
from who_onshow
left join shows on shows.id =pid
left join performer on performer.id =onid
where pid=@t
order by onsequence
end

exec arrange_se 3
 
 select * from sells
 update users set pw='1' where id=1520511410