var mqtt    = require('mqtt');
var find    = require('lodash.find');
var client  = mqtt.connect('mqtt://127.0.0.1');
var app = require('express')();
var server = app.listen(3000);
var io = require('socket.io')(server);

var topics = [
	{ id: 'hammock', availability: 0 },
	{ id: 'couch', availability: 0 },
	{ id: 'mens', availability: 0 },
	{ id: 'croom', availability: 0 },
];


app.get('/', function(req, res) {
    res.sendFile(__dirname + '/index.html');
});

io.on('connection', function(socket){
  console.log('a user connected');
  socket.on('disconnect', function(){
    console.log('user disconnected');
  });
  socket.on('chat message', function(msg){
    console.log('message: ' + msg);
  });
  socket.on('topic:hammock', function(msg){
    console.log('message: ' + msg);
  });
  socket.on('topic:couch', function(msg){
    console.log('message: ' + msg);
  });
  socket.on('topic:mens', function(msg){
    console.log('message: ' + msg);
  });
  socket.on('topic:croom', function(msg){
    console.log('message: ' + msg);
  });

  socket.on('request all topics available', function(){
  	topics.forEach(function(topic) {
		socket.emit('topic:' + topic.id, topic.availability);	
  	});
  });


});


// setup

client.on('connect', function () {
	topics.forEach(function(topic) {
		// subscribe mqtt
	  client.subscribe(topic.id);
	});
  // client.publish('presence', 'Hello mqtt');
});

client.on('message', function (topic, message) {

	var availability = message.toString();
	// console.log(topic, availability);
	
	var topicItem = find(topics, function(item) {
		// console.log(item.id);
		// console.log(item.id === topic);
		return item.id === topic;
	});

	// ignore if the new availability is same as old one
	if (!topicItem || topicItem.availability === availability) { return; }

	// console.log(topicItem);

	// update item
	topicItem.availability = availability;

	// broadcast to everybody!
	io.emit('topic:' + topicItem.id, availability);	

});

