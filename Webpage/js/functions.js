$( document ).ready(function() {

// PRELOADER
	setTimeout(function(){
		$('body').addClass('loaded');
	}, 3000);

// SCROLL REVEAL
	window.sr = new scrollReveal();


// PARALLAX IMAGES
	$('#subscribe').parallax("50%", 0.0);

// SMOOTH SCROLL
	smoothScroll.init({
		speed: 900,
		easing: 'easeInOutCubic',
		updateURL: true,
		offset: 0,
		callbackBefore: function ( toggle, anchor ) {},
		callbackAfter: function ( toggle, anchor ) {}
	});



// CONTACT FORM
	$("input, textarea").focus(function() {
		$(this).prev("label").hide();
		$(this).prev().prev("label").hide();
	});

	$("#contact_form").submit(function() {
		var name = $("#name").val();
		var phone = $("#phone").val();
		var email = $("#email").val();
		var comment = $("#comment").val();

			$('#contact_form').animate({opacity:'0.3'}, 500);

			var dataString = 'name='+ name + '&email=' + email + '&phone=' + phone + '&comment=' + comment;

			$.ajax({
				type: "POST",
				url: "form/sendmail.php",
				data: dataString,
				success: function() {
					$("#contact_form").animate({opacity:'1'}, 500);
					$('#contact_form').slideUp(300);
					$('#success').delay(2000).css("display", "block");
				}
			});
			return false;
	});

});
