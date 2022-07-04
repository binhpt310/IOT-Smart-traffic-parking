var token = localStorage.getItem("token")
var id_user = localStorage.getItem("id")
console.log(id_user)

const ws = new WebSocket("ws://localhost:8080");
ws.addEventListener("open", () =>{
  console.log("We are connected");
  ws.send("Hello server !!!");
});
 
ws.addEventListener('close', () => {
    console.log('The connection has been closed !!!');
})

ws.addEventListener('message', function (event) {
    console.log(event.data);
})