//
//  LPWebQuery.h
//  CalabashJS
//
//  Created by Karl Krukow on 27/06/12.
//  Copyright (c) 2012 LessPainful. All rights reserved.
//

#import <Foundation/Foundation.h>

static NSString *LP_QUERY_JS = @"(function(){function isHostMethod(object,property){var t=typeof object[property];return t==='function'||(!!(t==='object'&&object[property]))||t==='unknown';}var NODE_TYPES={1:'ELEMENT_NODE',2:'ATTRIBUTE_NODE',3:'TEXT_NODE',9:'DOCUMENT_NODE'};function computeRectForNode(object){var res={},boundingBox;if(isHostMethod(object,'getBoundingClientRect')){boundingBox=object.getBoundingClientRect();res['rect']=boundingBox;res['rect'].center_x=boundingBox.left+Math.floor(boundingBox.width/2);res['rect'].center_y=boundingBox.top+Math.floor(boundingBox.height/2);}res.nodeType=NODE_TYPES[object.nodeType]||res.nodeType+' (Unexpected)';res.nodeName=object.nodeName;res.id=object.id||'';res['class']=object.className||'';if(object.href){res.href=object.href;}if(object.hasOwnProperty('value')){res.value=object.value||'';}res.html=object.outerHTML||'';res.textContent=object.textContent;return res;}function toJSON(object){var res,i,N,spanEl,parentEl;if(typeof object==='undefined'){throw {message:'Calling toJSON with undefined'};}else{if(object instanceof Text){parentEl=object.parentElement;if(parentEl){spanEl=document.createElement('calabash');spanEl.style.display='inline';spanEl.innerHTML=object.textContent;parentEl.replaceChild(spanEl,object);res=computeRectForNode(spanEl);res.nodeType=NODE_TYPES[object.nodeType];delete res.nodeName;delete res.id;delete res['class'];parentEl.replaceChild(object,spanEl);}else{res=object;}}else{if(object instanceof Node){res=computeRectForNode(object);}else{if(object instanceof NodeList||(typeof object=='object'&&object&&typeof object.length==='number'&&object.length>0&&typeof object[0]!=='undefined')){res=[];for(i=0,N=object.length;i<N;i++){res[i]=toJSON(object[i]);}}else{if(NODE_TYPES[object.nodeType]!=='undefined'){res=computeRectForNode(object);}else{res=object;}}}}}return res;}var exp='%@',queryType='%@',nodes=null,res=[],i,N;try{if(queryType==='xpath'){nodes=document.evaluate(exp,document,null,XPathResult.ORDERED_NODE_SNAPSHOT_TYPE,null);for(i=0,N=nodes.snapshotLength;i<N;i++){res[i]=nodes.snapshotItem(i);}}else{if(queryType==='iframe'){var frames=document.querySelectorAll('iframe');var frameLength=frames.length;if(exp.indexOf('|')==-1){if(frameLength>0){var nodes=frames[0].contentWindow.document.body.querySelectorAll(exp);for(i=0,N=nodes.length;i<N;i++){res[i]=nodes[i];}}}else{var expArr=exp.split('|');var newExp=expArr[1];var iframeIndex=parseInt(expArr[0]);var nodes=frames[iframeIndex].contentWindow.document.body.querySelectorAll(newExp);for(i=0,N=nodes.length;i<N;i++){res[i]=nodes[i];}}}else{res=document.querySelectorAll(exp);}}}catch(e){return JSON.stringify({error:'Exception while running query: '+exp,details:e.toString()});}return JSON.stringify(toJSON(res));})();";

typedef enum LPWebQueryType
{
    LPWebQueryTypeCSS,
    LPWebQueryTypeXPATH,
    LPWebQueryTypeIFRAME,
    LPWebQueryTypeFreeText

} LPWebQueryType;

@interface LPWebQuery : NSObject

+(NSArray*)evaluateQuery:(NSString *)query
                  ofType:(LPWebQueryType)type
               inWebView:(UIWebView *)webView;

@end
