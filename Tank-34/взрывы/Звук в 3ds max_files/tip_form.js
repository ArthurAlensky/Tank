// Tipue 1.52


// ---------- script properties ----------


var results_location = "results.htm";


// ---------- end of script properties ----------


var engine = new Array()
engine[0]="http://www.yandex.ru:80/yandsearch?text="
engine[1]="http://search.rambler.ru/cgi-bin/rambler_search?words="
engine[2]="http://sm.aport.ru/scripts/template.dll?r="
engine[3]="http://results1.metabot.ru/?st="
engine[4]="http://go.mail.ru/search?lfilter=yes&use_morph=yes&change=2&q="
engine[5]="http://poisk.open.by/cgi-bin/search.cgi?query="
engine[6]="http://search.tut.by/?status=1&encoding=1&page=0&how=rlv&query="
engine[7]="http://www.lycos.com/cgi-bin/pursuit?query="
engine[8]="http://www.google.com/search?q="
engine[9]="http://www.hotbot.com/default.asp?MT="
engine[10]="http://search.yahoo.com/search?p="
engine[11]="http://altavista.digital.com/cgi-bin/query?q=" 
engine[12]="http://search.msn.com/results.aspx?q="

function search_form(tip_Form){
var srcEng =""
if (document.all.tip_Form[0].value==""){
alert("А что, собственно, будем искать?");
return;
}
for(var i=0; i < document.all.service.length; i++){
if (document.all.service[i].selected){
srcEng = document.all.service[i].text
if(i == 13)
        { 
	if (tip_Form.d.value.length > 0) {
		document.cookie = 'd=' + escape(tip_Form.d.value) + '; path=/';
		document.cookie = 'n=0; path=/';
		window.location = results_location;}
return;
}		                                          //Поиск на сайте
else 
myURL =engine[i]+document.all.tip_Form[0].value;   // Ссылка на поисковик 
window.open(myURL, "");
}
}
}







