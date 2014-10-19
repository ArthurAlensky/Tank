
var visibleVar="null"; 
function init(){

if (navigator.appName == "Netscape") {
layerRef="document.layers"; 
styleSwitch=""; 
visibleVar="show";
}else{
layerRef="document.all"; 
styleSwitch=".style"; 
visibleVar="visible";
}
} 
function showHideLayerSwitch(layerName){
if (eval(layerRef+'["'+layerName+'"]'+styleSwitch+'.visibility == visibleVar')){ 
hideLayer(layerName); 
}else{ 
showLayer(layerName); 
}
} 
function showLayer(layerName){
eval(layerRef+'["'+layerName+'"]'+styleSwitch+'.visibility="visible"');
} 
function hideLayer(layerName){
eval(layerRef+'["'+layerName+'"]'+styleSwitch+'.visibility="hidden"');
} 

function showHideRightColl(){
if( document.all.rightColl.style.display=='none'){ 
document.all.rightColl.style.display='block'; 
document.all.box.innerHTML='<a href="#"class="butt"onClick="showHideRightColl(); return false;"><br>скрыть панель</a>';
}
else{ 
document.all.rightColl.style.display='none'; 
document.all.box.innerHTML='<a href="#"class="butt"onClick="showHideRightColl(); return false;"><br>отобразить панель</a>';
}
}
//Загрузка картинок в новое окно
function load_Image(path, w,h)
			{
			var w=w+10
			var h=h+10
		var features = "height="+ h +", width=" + w +", location=no, resizable=no, scrollbars=none, toolbar=no";   
		 var newWindow = open("", "_blank", features);
            newWindow.document.writeln("<body bgcolor='#999966' style=\"{ margin: 5 }\">");
             newWindow.document.writeln("<img  alt='Image loading...' src=\"" + path  +"\">");
            newWindow.document.writeln("</body>");
		newWindow.document.title = "Easy Render picture";
			}
