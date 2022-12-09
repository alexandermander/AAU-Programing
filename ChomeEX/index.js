var checkbox = document.getElementById("checkbox")

if (checkbox.checked == true) {
    chrome.tabs.query({active: true, currentWindow:true},function(tabs){
        chrome.tabs.sendMessage(tabs[0].id, {
            req: "send"
        })
    })
    
}


document.getElementById("upload-button").addEventListener("click", () =>{
    chrome.tabs.query({active: true, currentWindow:true},function(tabs){
        chrome.tabs.sendMessage(tabs[0].id, {
            req: "send"
        })
    })
    
})


