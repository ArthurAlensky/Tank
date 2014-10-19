/* Author:
Dark — aqrt.ru
*/

$(function() {
    stop = true;
    $('#xf-submit').click(function(event) {
        if (stop == true) {
            event.preventDefault();
            $.ajax({
                type: "POST",
                url: '/user/checkpass.php',
                data: 'login='+$('#LoginControl').attr('value') +'&password='+$('#ctrl_password').attr('value'),
                success: function (data) {
                    if (data) {
                        stop = false;
                        $('#xf-submit').trigger('click');
                    }
                }
            });
        } else {
            return;
        }
    });
	 
    anim($('#header_logo'));
    anim($('#footer_logo'));
    function anim(block) {
        block.hover( function() { trig=1; repeat(); }, function() { trig=0; } );
        var trig = 0;
        function repeat() {
            if (trig)
                block.animate({backgroundColor: $.Color(block.css('backgroundColor')).hue('+=6')}, 30, repeat);
        } 
    }


	//IE shadow effect support
        /*
	if ( $.browser.msie ) {
		$('header[role="banner"] nav.main_menu li').textShadow();
		$('.visual_content').textShadow();
	}
	*/
	//Personal menu control
	var old_top = $('.personal_menu').css('top');
	var open_time = 300;
	$('.tab_open_switch').toggle(
		function (event) {
			event.preventDefault();
			$('.personal_menu').animate({
				top: '-1px'
			}, open_time, function() {
				$('.arrows_wrap').addClass('opened');
			});
		},
		function (event) {
			event.preventDefault();
			$('.personal_menu').animate({
				top: old_top
			}, open_time, function() {
				$('.arrows_wrap').removeClass('opened');
			});
		}
	);
	
	//ACCORDION BUTTON ACTION	
	$('div.accordion_button').click(function() {
		$('div.accordion_content.active').removeClass('active');
		$(this).next().slideDown('normal').addClass('active');
		$('div.accordion_content:not(.active)').slideUp('normal');
	});
	
	//Carousel
        $('.visual_carousel').show().carousel( { direction: 'vertical', pagination: true, nextBtn: 0, prevBtn: 0, autoSlide:false} );

 
	//HIDE THE DIVS ON PAGE LOAD	
	$('div.accordion_content:not(.selected)').hide();
	
	$('.main_logo').hover(function() {
		var hue = 'rgb('
			+ (Math.floor(Math.random() * 256)) + ','
			+ (Math.floor(Math.random() * 256)) + ','
			+ (Math.floor(Math.random() * 256)) + ')';
	   $(this).stop().animate( { backgroundColor: hue }, 500);
	},function() {
	   $(this).stop().animate( { backgroundColor: '#000' }, 500);
	});

    $('#gw_descr_text a.author_comment_title').toggle(function() {
       $('#gw_descr_text .author_comment').animate({height: "show"}, 300);
       $('#gw_descr_text a.author_comment_title').css({background: 'url(../img/gallery/gallery_work_author_comment.png) no-repeat'})
       return false;
    }, function() {
       $('#gw_descr_text .author_comment').animate({height: "hide"}, 300);
       $('#gw_descr_text a.author_comment_title').css({background: 'url(../img/gallery/gallery_work_author_comment_show.png) no-repeat'})
       return false;
    });
    $('#oth_work_tip a').toggle(function() {
       $('#gw_other_list').animate({height: "show"}, 300);
       return false;
    }, function() {
       $('#gw_other_list').animate({height: "hide"}, 300);
       return false;
    });
    $('.box_showhide a.sh_swich').toggle(function() {
       $('.box_showhide .' + $(this).attr('box')).animate({height: "show"}, 300);
       return false;
    }, function() {
       $('.box_showhide .' + $(this).attr('box')).animate({height: "hide"}, 300);
       return false;
    });
    $('#contact_form_show').click(function() {
        $('#contact_form').show();
    });
    $('#contact_form_close').click(function() {
        $('#contact_form').hide();
    });
    $('#blogchangemenu').toggle(function menu_show() {
        $('nav.main_menu, #header_logo').show();
        $('#main-logo-small').hide();
        $('div.changemenu').addClass('changemenu_opened');
        $('header .fixed_width_block').css('height', '120px');
        return false;
    }, function menu_hide() {
        $('nav.main_menu, #header_logo').hide();
        $('#main-logo-small').show();
        $('div.changemenu').removeClass('changemenu_opened');
        $('header .fixed_width_block').css('height', '40px');
        return false;
    });
    $("a.userinfoform").fancybox({
        minWidth	: 450,
        fitToView	: false,
        width           : '70%',
        height          : '70%',
        autoSize	: true,
        closeBtn        : true,
        closeClick	: false,
        openEffect	: 'none',
        closeEffect	: 'none',
        autoCenter      : false,
        padding         : 6
    });
    $('#img6_show_award').click(function() {
        $('#img6_box li.img6_blok1').show();
        $('#img6_box li.img6_blok2, #img6_box li.img6_blok3').hide();
        $('#img6_show_award').addClass('active');
        $('#img6_show_pub, #img6_show_discus').removeClass('active');
        return false;
    });
    $('#img6_show_pub').click(function() {
        $('#img6_box li.img6_blok2').show();
        $('#img6_box li.img6_blok1, #img6_box li.img6_blok3').hide();
        $('#img6_show_pub').addClass('active');
        $('#img6_show_award, #img6_show_discus').removeClass('active');
        return false;
    });
    $('#img6_show_discus').click(function() {
        $('#img6_box li.img6_blok3').show();
        $('#img6_box li.img6_blok1, #img6_box li.img6_blok2').hide();
        $('#img6_show_discus').addClass('active');
        $('#img6_show_award, #img6_show_pub').removeClass('active');
        return false;
    });

    var lenta_in_login = $("#lenta_in_login" ).height();
    if (lenta_in_login>0){
        $.ajax({
          url: "http://www.render.ru/lenta/get_lenta.php",
          type: "GET",
          cache:true,
          data: {data:1},
          success: function(data){
            $("#lenta_in_login").html(data);
            old_top = 89-$("#lenta_in_login" ).height()-370;
            $(".personal_menu").css("top",old_top);

          }
        });
    }
});

function openWindow(theURL,winName,features) {
    self.name ='site_main';
    window.open(theURL,winName,features+",statusbar=1,width=10,height=10");
}

