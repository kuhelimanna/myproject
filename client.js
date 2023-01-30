const socket = io()
let name;
let textarea = document.querySelector('#textarea')
let messageArea = document.querySelector('.message__area')
var audio = new Audio('ting.mp3');
do {
    name = prompt('Please enter your name: ')
    
} while(!name)
socket.emit('new-user-joined', name);


const append = (message, position)=>{
    const messageElement = document.createElement('div');
    messageElement.innerText = message;
    messageElement.classList.add('message');
    messageElement.classList.add(position);
    messageArea.appendChild(messageElement);
   if(position =='left'){ 
        audio.play();
    }
}
textarea.addEventListener('keyup', (e) => {
    if(e.key === 'Enter') {
       sendMessage(e.target.value)
    }
})



function sendMessage(message) {
    let msg = {
        user: name,
        message: message.trim()
        
    }
    //console.log(message);
    // Append 
    appendMessage(msg, 'outgoing')
    textarea.value = ''//clear the text box
    scrollToBottom()

    // Send to server 
    socket.emit('message', msg)

}

function appendMessage(msg, type) {
    let mainDiv = document.createElement('div')
    let className = type
    mainDiv.classList.add(className, 'message')
    
        let markup = `
        <h4>${msg.user}</h4>
        <p>${msg.message}</p>
    `
    mainDiv.innerHTML = markup
    messageArea.appendChild(mainDiv)
}

//New user join
socket.on('user-joined', name =>{
    append(`${name} joined the chat`, 'join')
    scrollToBottom()
})
// Recieve messages 
socket.on('message', (msg) => {
    appendMessage(msg, 'incoming')
    scrollToBottom()
})


socket.on('left', name =>{
    append(`${name} left the chat`, 'left')
    scrollToBottom()
})
  

function scrollToBottom() {
    messageArea.scrollTop = messageArea.scrollHeight
}