
var day="";
var month="";
var myweekday="";
var year="";
mydate = new Date();
myday = mydate.getDay();
mymonth = mydate.getMonth();
myweekday= mydate.getDate();
weekday= myweekday;
myyear= mydate.getYear();
year = 2006 //myyear
if(myday == 0)
day = " Воскр., "      
else if(myday == 1)
day = " Понед., "
else if(myday == 2)
day = " Вторник, "   
else if(myday == 3)
day = " Среда, "   
else if(myday == 4)
day = " Четверг, "
else if(myday == 5)
day = " Пятница, "
else if(myday == 6)
day = " Суббота, "
if(mymonth == 0) {
month = " января "}
else if(mymonth ==1)
month = " февраля "
else if(mymonth ==2)
month = " марта "
else if(mymonth ==3)
month = " апреля "
else if(mymonth ==4)
month = " майя "
else if(mymonth ==5)
month = " июня "
else if(mymonth ==6)
month = " июля "
else if(mymonth ==7)
month = " августа "
else if(mymonth ==8)
month = " сентября "
else if(mymonth ==9)
month = " октября "
else if(mymonth ==10)
month = " ноября "
else if(mymonth ==11)
month = " декабря "




