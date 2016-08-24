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

          el.innerHTML = id + ': ' + availability;
        });
      });
      console.log(topics);

      // request all topics available
      socket.emit('request all topics available');
