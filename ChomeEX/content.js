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
if(time>8 && time < 16 && document.domain == 'www.youtube.com'){
    run()
}

function run(){
    document.body.innerHTML = "Sander SE ikke youType lige nu, lav noget Produktivt"
    const myHtml = document.all[0];
    myHtml.style.fontSize = '50px'
    myHtml.style.textAlign = 'center'
    myHtml.style.color = 'white'
    myHtml.style.padding = '100px'

}