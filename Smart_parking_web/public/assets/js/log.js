const ws = new WebSocket("ws://localhost:8081")

ws.addEventListener("open", () =>{
    console.log("We are connected");
    ws.send("Hello server, I'm log page!!!");
  });
   
ws.addEventListener('close', () => {
    console.log('The connection has been closed !!!');
})

ws.addEventListener('message', function (event) {
    console.log(event.data)
})