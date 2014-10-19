var wait = 50 		
var message = new Array()
message[0] = "Добро пожаловать на сайт 3D графики ...          "
message[1] = "         Easy Render               "
message[2] = "www.easy-render.nm.ru       e-mail: vlad_62@newmail.ru          "
var msgs = 2 		

var temp = ""		
var curmsg = 0
var as = 0
var counter = 0

function typew()
{
as = as + 1
check()
window.status = message[curmsg].substring(0, as)
if(as == message[curmsg].length + 5)
{
curmsg = curmsg + 1
as = 0
}
if(curmsg > msgs)
{
curmsg = 0 }
counter = setTimeout("typew()", wait)
}
function check()
{
if(as <= message[curmsg].length)
{
if(message[curmsg].substring(as, as + 1) == "")
{
as = as + 1
check()
}
}
}
typew();









