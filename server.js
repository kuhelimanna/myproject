const express = require('express')
const app = express()
const http = require('http').createServer(app)

const PORT = process.env.PORT || 3000

http.listen(PORT, () => {
    console.log(`Listening on port ${PORT}`)
})

app.use(express.static(__dirname + '/public'))

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/index.html')
})

// Socket 
const io = require('socket.io')(http)
//var user;
const _users = {};
io.on('connection', (socket) => {
    
    console.log('Connected... ')
    socket.on('new-user-joined', name =>{ 
        _users[socket.id] = name;
        socket.broadcast.emit('user-joined', name);
    });
   
    socket.on('message', (msg) => {
        socket.broadcast.emit('message', msg)
       
        //console.log(msg);

    })
    
    socket.on('disconnect', message =>{
        socket.broadcast.emit('left', _users[socket.id]);
        delete _users[socket.id];
    });
    
})