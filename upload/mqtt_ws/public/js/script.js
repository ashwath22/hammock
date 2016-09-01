$(document).ready(function() {
            $('#fullpage').fullpage();  
        });


var socket = io();

      var topics = [
        { id: 'hammock' },
        { id: 'couch' },
        { id: 'mens' },
        { id: 'croom' },
      ];

      // set all topics
      topics.forEach(function(topic) {
        var id = topic.id;
        // set DOM element
        var el = topic.el = document.getElementById(id);
        // subscribe
        var channel = topic.channel = 'topic:' + id;
        socket.on(channel, function(availability){
          // console.log(channel, availability);
          // store
          topic.availability = availability;
          // show availability into element
          console.log(availability);
          // el.innerHTML = id + ': ' + availability;

          // $.keyframe.define([{
          //   name: 'dash',
          //   '0%': {strokeDashoffset: 1000;},
          //   '100%': {strokeDashoffset: 0;}
          // }]);


          if (availability === "1") {
            console.log("holla!!");
            $('body').addClass('undo1');
          } else if (availability === "0") {
            console.log("bye!!");
            $('body').removeClass('undo1');
          }

                if (availability === "2") {
            console.log("holla!!");
            $('body').addClass('undo2');
          } else if (availability === "0") {
            console.log("bye!!");
            $('body').removeClass('undo2');
          }

          if (availability === "3") {
            console.log("holla!!");
            $('body').addClass('undo3');
          } else if (availability === "0") {
            console.log("bye!!");
            $('body').removeClass('undo3');
          }

          if (availability === "4") {
            console.log("holla!!");
            $('body').addClass('undo4');
          } else if (availability === "0") {
            console.log("bye!!");
            $('body').removeClass('undo4');
          }

      
            // $('.path').playKeyframe({
            //   name: 'dash',
            //   duration: 2000

            // });
        //     $('.upstairsToilet').css('visibility', 'hidden');
        // } 
        // else {
        //   $('.upstairsToilet').css('visibility', 'visible');
        // }
  
        });
      });
      console.log(topics);


      // request all topics available
      socket.emit('request all topics available');

   
$( document ).ready(function() {
    console.log( "ready!" );
    

//    $('.nav').click(function(){
//       $.fn.fullpage.destroy('all');
//    });

//    $('.nav').click(function(){
//      if ( $('#fullpage').css('visibility') == 'visible')
//        $('#fullpage').css('visibility','hidden');
//        else $('#fullpage').css('visibility','visible');
//});
//    $('.nav').click(function(){
//      if ( $('#fullpage').css('visibility') == 'visible')
//        $('#listpage').css('visibility','hidden');
//        else $('#listpage').css('visibility','visible');
//});

//    $('.nav').click(function(){
//            $('#fullpage').toggle('#fullpage');
//});
//    
//    $('.toiletList').click(function(){
//            $('#fullpage').toggle('#fullpage');
//});
    
//        $('.nav').click(function(){
//            $('.listpage').toggle('.showListpage');
//            console.log("TOP");
//});
    
    $(".nav").click(function () {
                $(".listpage").animate({
                    top: "-=100vh"
                }, 1000);
                return false;
            });
    
//     $(document).ready(function(){
//         $('.splashPage').delay(3200).queue(function (next) { 
//             $('.splashPage').css('display', 'none'); 
//             next(); 
//   });
     
// });
    
    
});


