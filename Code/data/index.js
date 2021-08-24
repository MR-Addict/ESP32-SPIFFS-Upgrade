var websocket = new WebSocket("ws://" + location.hostname + ":81/");
websocket.onopen = function (event) {
  onOpen(event);
};
websocket.onclose = function (event) {
  onClose(event);
};
websocket.onmessage = function (event) {
  onMessage(event);
};
websocket.onerror = function (event) {
  onError(event);
};
function Send_Data(element) {
  var command;
  if (element.checked) command = "LED ON";
  else command = "LED OFF";
  websocket.send(command);
}
function onOpen(event) {
  console.log("Server Connected!");
  alert("Server Connected!");
}
function onClose(event) {
  console.log("Server Disconnected!");
  alert("Server Disconnected!");
}
function onMessage(event) {
  var message;
  var Switch_Status;
  if (event.data == "LED ON") {
    message = "LED ON";
    Switch_Status = true;
  } else {
    message = "LED OFF";
    Switch_Status = false;
  }
  console.log(message);
  document.getElementById("LED").innerHTML = message;
  document.getElementById("output").checked = Switch_Status;
}
function onError(event) {
  console.log("Error:" + event.data);
  alert("Error Occured!");
}
