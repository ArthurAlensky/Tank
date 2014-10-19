$(function() {
    var fnComments = function(){
        var fnOver = function(){
            $(this)
                .find('.comment')
                .addClass('selected')
                .end()
                .find('.coms_toolbar')
                .animate({opacity: 1}, 'slow');
        };
        var fnOut = function(){
            $(this)
                .find('.comment')
                .removeClass('selected')
                .end()
                .find('.coms_toolbar')
                .animate({opacity: 0});
        };
        $('.comments_container').hoverIntent(fnOver, fnOut);
    };
    $(document).ready(fnComments);
});
function openWindow(theURL,winName,features) {
    self.name ='site_main';
  window.open(theURL,winName,features+",statusbar=1,width=10,height=10");
}