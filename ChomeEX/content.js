//chrome.runtime.onMessage.addListener(
//    function(request,sender,sendResponse){
//        try{
//            if (request.req == "send") {
//                run();                
//            }  
//            
//        }
//        catch (error){
//            console.log(error)
//            sendResponse({status: "not working"})
//        }
//    }
//)

const d = new Date();
let time = d.getHours();
console.log(time)
if(time>9&& time < 16 && document.domain == 'www.youtube.com' || document.domain == 'www.instagram.com'){
    run()
}
function run(){
    if (document.domain == 'www.youtube.com') {
        var fyldOrd = "youType"
        var color = 'white'

    }else if (document.domain == 'www.instagram.com') {
        var fyldOrd = "instGram"
        var color = 'black'
    } 
    document.body.innerHTML =  "Sander SE ikke " + fyldOrd + " lige nu, lav noget Produktivt"
    const myHtml = document.all[0];
    myHtml.style.fontSize = '50px'
    myHtml.style.textAlign = 'center'
    myHtml.style.color = color
    myHtml.style.padding = '100px'

}