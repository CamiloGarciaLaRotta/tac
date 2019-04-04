let url: unit => unit = [%bs.raw
  {|
function () {
  console.log(1);
  chrome.runtime.onMessage.addListener(
    function(request, sender, sendResponse) {
      console.log(2);
      if( request.message === "url" ) {
        console.log(3);
        let url = window.location.href;
        console.log("foo " + url);
        chrome.runtime.sendMessage({"url": url});
      }
    }
  );
}
|}
];

url();
