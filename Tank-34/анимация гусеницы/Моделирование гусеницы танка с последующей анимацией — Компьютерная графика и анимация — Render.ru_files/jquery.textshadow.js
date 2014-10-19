jQuery.fn.textShadow = function () {
    return this.each(function () {
        var el = $(this);
		var ex_html = el.html();

        el.html('<span class="jquery-text-shadow-text">' + ex_html + '</span>');
        $('<span class="jquery-text-shadow">' + ex_html + '</span>').appendTo(el);
		$('.jquery-text-shadow a').contents().unwrap();
		
    });
};