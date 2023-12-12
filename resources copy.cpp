#include "resources.h"

const char index_html[] PROGMEM = R"rawliteral(
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <link rel="icon" type="image/svg+xml" href="/icon.svg" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>ESP8266 Intervalometer</title>
    <script type="module">var re=Object.defineProperty;var oe=(t,e,n)=>e in t?re(t,e,{enumerable:!0,configurable:!0,writable:!0,value:n}):t[e]=n;var T=(t,e,n)=>(oe(t,typeof e!="symbol"?e+"":e,n),n);(function(){const e=document.createElement("link").relList;if(e&&e.supports&&e.supports("modulepreload"))return;for(const o of document.querySelectorAll('link[rel="modulepreload"]'))r(o);new MutationObserver(o=>{for(const i of o)if(i.type==="childList")for(const u of i.addedNodes)u.tagName==="LINK"&&u.rel==="modulepreload"&&r(u)}).observe(document,{childList:!0,subtree:!0});function n(o){const i={};return o.integrity&&(i.integrity=o.integrity),o.referrerPolicy&&(i.referrerPolicy=o.referrerPolicy),o.crossOrigin==="use-credentials"?i.credentials="include":o.crossOrigin==="anonymous"?i.credentials="omit":i.credentials="same-origin",i}function r(o){if(o.ep)return;o.ep=!0;const i=n(o);fetch(o.href,i)}})();function h(){}function ee(t){return t()}function G(){return Object.create(null)}function I(t){t.forEach(ee)}function te(t){return typeof t=="function"}function L(t,e){return t!=t?e==e:t!==e||t&&typeof t=="object"||typeof t=="function"}function ie(t){return Object.keys(t).length===0}function ce(t,...e){if(t==null){for(const r of e)r(void 0);return h}const n=t.subscribe(...e);return n.unsubscribe?()=>n.unsubscribe():n}function A(t,e,n){t.$$.on_destroy.push(ce(e,n))}function O(t,e,n){return t.set(n),e}function g(t,e){t.appendChild(e)}function y(t,e,n){t.insertBefore(e,n||null)}function _(t){t.parentNode&&t.parentNode.removeChild(t)}function m(t){return document.createElement(t)}function b(t){return document.createTextNode(t)}function C(){return b(" ")}function se(){return b("")}function q(t,e,n,r){return t.addEventListener(e,n,r),()=>t.removeEventListener(e,n,r)}function E(t,e,n){n==null?t.removeAttribute(e):t.getAttribute(e)!==n&&t.setAttribute(e,n)}function ue(t){return Array.from(t.childNodes)}function J(t,e){e=""+e,t.data!==e&&(t.data=e)}function H(t,e){t.value=e??""}let K;function P(t){K=t}const k=[],Q=[];let x=[];const W=[],le=Promise.resolve();let B=!1;function fe(){B||(B=!0,le.then(ne))}function M(t){x.push(t)}const j=new Set;let v=0;function ne(){if(v!==0)return;const t=K;do{try{for(;v<k.length;){const e=k[v];v++,P(e),ae(e.$$)}}catch(e){throw k.length=0,v=0,e}for(P(null),k.length=0,v=0;Q.length;)Q.pop()();for(let e=0;e<x.length;e+=1){const n=x[e];j.has(n)||(j.add(n),n())}x.length=0}while(k.length);for(;W.length;)W.pop()();B=!1,j.clear(),P(t)}function ae(t){if(t.fragment!==null){t.update(),I(t.before_update);const e=t.dirty;t.dirty=[-1],t.fragment&&t.fragment.p(t.ctx,e),t.after_update.forEach(M)}}function de(t){const e=[],n=[];x.forEach(r=>t.indexOf(r)===-1?e.push(r):n.push(r)),n.forEach(r=>r()),x=e}const N=new Set;let pe;function z(t,e){t&&t.i&&(N.delete(t),t.i(e))}function X(t,e,n,r){if(t&&t.o){if(N.has(t))return;N.add(t),pe.c.push(()=>{N.delete(t),r&&(n&&t.d(1),r())}),t.o(e)}else r&&r()}function Y(t){t&&t.c()}function D(t,e,n){const{fragment:r,after_update:o}=t.$$;r&&r.m(e,n),M(()=>{const i=t.$$.on_mount.map(ee).filter(te);t.$$.on_destroy?t.$$.on_destroy.push(...i):I(i),t.$$.on_mount=[]}),o.forEach(M)}function F(t,e){const n=t.$$;n.fragment!==null&&(de(n.after_update),I(n.on_destroy),n.fragment&&n.fragment.d(e),n.on_destroy=n.fragment=null,n.ctx=[])}function ge(t,e){t.$$.dirty[0]===-1&&(k.push(t),fe(),t.$$.dirty.fill(0)),t.$$.dirty[e/31|0]|=1<<e%31}function R(t,e,n,r,o,i,u=null,f=[-1]){const l=K;P(t);const c=t.$$={fragment:null,ctx:[],props:i,update:h,not_equal:o,bound:G(),on_mount:[],on_destroy:[],on_disconnect:[],before_update:[],after_update:[],context:new Map(e.context||(l?l.$$.context:[])),callbacks:G(),dirty:f,skip_bound:!1,root:e.target||l.$$.root};u&&u(c.root);let d=!1;if(c.ctx=n?n(t,e.props||{},(s,a,...p)=>{const $=p.length?p[0]:a;return c.ctx&&o(c.ctx[s],c.ctx[s]=$)&&(!c.skip_bound&&c.bound[s]&&c.bound[s]($),d&&ge(t,s)),a}):[],c.update(),d=!0,I(c.before_update),c.fragment=r?r(c.ctx):!1,e.target){if(e.hydrate){const s=ue(e.target);c.fragment&&c.fragment.l(s),s.forEach(_)}else c.fragment&&c.fragment.c();e.intro&&z(t.$$.fragment),D(t,e.target,e.anchor),ne()}P(l)}class U{constructor(){T(this,"$$");T(this,"$$set")}$destroy(){F(this,1),this.$destroy=h}$on(e,n){if(!te(n))return h;const r=this.$$.callbacks[e]||(this.$$.callbacks[e]=[]);return r.push(n),()=>{const o=r.indexOf(n);o!==-1&&r.splice(o,1)}}$set(e){this.$$set&&!ie(e)&&(this.$$.skip_bound=!0,this.$$set(e),this.$$.skip_bound=!1)}}const he="4";typeof window<"u"&&(window.__svelte||(window.__svelte={v:new Set})).v.add(he);function me(t){let e;return{c(){e=m("style"),e.textContent=`:root {
      --gray-5: var(--white);
      --gray-15: var(--lighter);
      --gray-35: var(--light);
      --gray-50: var(--medium);
      --gray-65: var(--dark);
      --gray-85: var(--darker);
      --gray-95: var(--black);
      --green-5: var(--light-green);
      --green-95: var(--dark-green);
      --red-5: var(--light-red);
      --red-95: var(--dark-red);
    }`},m(n,r){y(n,e,r)},d(n){n&&_(e)}}}function _e(t){let e;return{c(){e=m("style"),e.textContent=`:root {
      --gray-5: var(--black);
      --gray-15: var(--darker);
      --gray-35: var(--dark);
      --gray-50: var(--medium);
      --gray-65: var(--light);
      --gray-85: var(--lighter);
      --gray-95: var(--white);
      --green-5: var(--dark-green);
      --green-95: var(--light-green);
      --red-5: var(--dark-red);
      --red-95: var(--light-red);
    }`},m(n,r){y(n,e,r)},d(n){n&&_(e)}}}function ye(t){let e,n,r,o,i,u,f;function l(s,a){return s[0]=="light"?_e:me}let c=l(t),d=c(t);return{c(){e=m("button"),n=b("Theme is "),r=b(t[0]),o=C(),d.c(),i=se()},m(s,a){y(s,e,a),g(e,n),g(e,r),y(s,o,a),d.m(s,a),y(s,i,a),u||(f=q(e,"click",t[1]),u=!0)},p(s,[a]){a&1&&J(r,s[0]),c!==(c=l(s))&&(d.d(1),d=c(s),d&&(d.c(),d.m(i.parentNode,i)))},i:h,o:h,d(s){s&&(_(e),_(o),_(i)),d.d(s),u=!1,f()}}}function be(t,e,n){let r=localStorage.getItem("theme")||(window.matchMedia("(prefers-color-scheme: dark)").matches?"dark":"light");return[r,()=>{n(0,r=r=="light"?"dark":"light"),localStorage.setItem("theme",r)}]}class $e extends U{constructor(e){super(),R(this,e,be,ye,L,{})}}const w=[];function V(t,e=h){let n;const r=new Set;function o(f){if(L(t,f)&&(t=f,n)){const l=!w.length;for(const c of r)c[1](),w.push(c,t);if(l){for(let c=0;c<w.length;c+=2)w[c][0](w[c+1]);w.length=0}}}function i(f){o(f(t))}function u(f,l=h){const c=[f,l];return r.add(c),r.size===1&&(n=e(o,i)||h),f(t),()=>{r.delete(c),r.size===0&&n&&(n(),n=null)}}return{set:o,update:i,subscribe:u}}const S=V(!1),Z=V("192.168.4.7"),ve=V("http://192.168.4.1");function we(t){let e;return{c(){e=m("p"),e.textContent="Disconnected",E(e,"class","warning")},m(n,r){y(n,e,r)},p:h,d(n){n&&_(e)}}}function ke(t){let e,n,r,o;return{c(){e=m("p"),n=b("Disconnected ("),r=b(t[1]),o=b(")"),E(e,"class","warning")},m(i,u){y(i,e,u),g(e,n),g(e,r),g(e,o)},p(i,u){u&2&&J(r,i[1])},d(i){i&&_(e)}}}function Ce(t){let e,n,r;return{c(){e=m("p"),n=b("Connected to "),r=b(t[4]),E(e,"class","success")},m(o,i){y(o,e,i),g(e,n),g(e,r)},p(o,i){i&16&&J(r,o[4])},d(o){o&&_(e)}}}function xe(t){let e;return{c(){e=m("p"),e.textContent="Connecting..."},m(n,r){y(n,e,r)},p:h,d(n){n&&_(e)}}}function Pe(t){let e,n,r,o,i,u,f,l,c;function d(p,$){return p[2]?xe:p[3]?Ce:p[1]!=""?ke:we}let s=d(t),a=s(t);return{c(){e=m("div"),n=m("h2"),n.textContent="Connect camera",r=C(),o=m("input"),i=C(),u=m("button"),u.textContent="Connect",f=C(),a.c(),E(o,"placeholder","Camera IP address"),E(e,"class","section")},m(p,$){y(p,e,$),g(e,n),g(e,r),g(e,o),H(o,t[0]),g(e,i),g(e,u),g(e,f),a.m(e,null),l||(c=[q(o,"input",t[6]),q(u,"click",t[5])],l=!0)},p(p,[$]){$&1&&o.value!==p[0]&&H(o,p[0]),s===(s=d(p))&&a?a.p(p,$):(a.d(1),a=s(p),a&&(a.c(),a.m(e,null)))},i:h,o:h,d(p){p&&_(e),a.d(),l=!1,I(c)}}}function Ee(t,e,n){let r,o,i;A(t,S,s=>n(3,r=s)),A(t,Z,s=>n(4,o=s)),A(t,ve,s=>n(7,i=s));let u=o,f="",l=!1;const c=async()=>{O(Z,o=u,o),n(2,l=!0);try{const s=await fetch(`${i}/connect`,{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify({cameraIP:o})});s.ok?O(S,r=!0,r):(n(1,f=`${s.status} error, ${s.statusText}`),O(S,r=!1,r))}catch{n(1,f="No response from ESP"),O(S,r=!1,r)}n(2,l=!1)};function d(){u=this.value,n(0,u)}return[u,f,l,r,o,c,d]}class Ie extends U{constructor(e){super(),R(this,e,Ee,Pe,L,{})}}function Oe(t){let e,n,r,o,i,u,f;return o=new $e({}),u=new Ie({}),{c(){e=m("main"),n=m("h1"),n.textContent="ESP8266 Intervalometer",r=C(),Y(o.$$.fragment),i=C(),Y(u.$$.fragment)},m(l,c){y(l,e,c),g(e,n),g(e,r),D(o,e,null),g(e,i),D(u,e,null),f=!0},p:h,i(l){f||(z(o.$$.fragment,l),z(u.$$.fragment,l),f=!0)},o(l){X(o.$$.fragment,l),X(u.$$.fragment,l),f=!1},d(l){l&&_(e),F(o),F(u)}}}class Se extends U{constructor(e){super(),R(this,e,null,Oe,L,{})}}new Se({target:document.getElementById("app")});</script>
    <style>:root{font-family:Inter,system-ui,Avenir,Helvetica,Arial,sans-serif;line-height:1.5;font-weight:400;font-size:16px;box-sizing:border-box;color:var(--gray-5);background-color:var(--gray-95)}*,*:before,*:after{box-sizing:inherit}body,h1,h2,h3,h4,h5,h6,p,ol,ul{margin:0;padding:0;font-weight:400}ol,ul{list-style:none}img{max-width:100%;height:auto}a{font-weight:500;color:#646cff;text-decoration:inherit}a:hover{color:#535bf2}body{margin:0;display:flex;place-items:center;min-width:320px;min-height:100vh}main{display:flex;flex-direction:column;row-gap:32px}.section{border-style:solid;border-width:2px;border-color:var(--gray-50);border-radius:16px;padding:16px;display:flex;flex-direction:column;row-gap:16px}#app{max-width:1280px;margin:0 auto;padding:2rem}button{border-radius:8px;border:1px solid transparent;padding:.6em 1.2em;font-size:1em;font-weight:500;font-family:inherit;color:var(--gray-95);background-color:var(--gray-5);cursor:pointer;transition:background-color .2s}button:hover{background-color:var(--gray-35)}input{border-width:2px;border-color:transparent;border-style:solid;border-radius:8px;padding:.6em;outline:none;font-size:1em;font-family:inherit;color:var(--gray-5);background-color:var(--gray-85)}input:hover{border-color:var(--gray-65)}input:focus{border-color:var(--gray-50)}.success{color:var(--green-5)}.warning{color:var(--red-5)}:root{--black:#121212;--white:#e6e6e6;--dark:#4c4c4c;--light:#a5a5a5;--darker:#2d2d2d;--lighter:#c5c5c5;--medium:#888888;--light-red:#ff8484;--dark-red:#b70000;--light-green:#87ff85;--dark-green:#028100}</style>
  </head>
  <body>
    <div id="app"></div>
  </body>
</html>
)rawliteral";

const char icon_svg[] PROGMEM = R"rawliteral(
<svg class="iconify iconify--logos" width="32" height="32" aria-hidden="true" preserveAspectRatio="xMidYMid" role="img" version="1.1" viewBox="0 0 256.96 257" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink"><defs><radialGradient id="radialGradient9277" cx="128.48" cy="128.5" r="96.375" gradientUnits="userSpaceOnUse"><stop stop-color="#e6e6e6" offset="0"/><stop stop-color="#c6c6c6" offset=".67716"/><stop stop-color="#a5a5a5" offset="1"/></radialGradient><clipPath id="clipPath10832"><circle cx="128.48" cy="128.5" r="128.5" fill="none" style="paint-order:normal"/></clipPath></defs><g clip-path="url(#clipPath10832)"><rect x="-.01819" width="257" height="257" fill="#121212" style="paint-order:normal"/><circle cx="128.48" cy="128.5" r="96.375" fill="url(#radialGradient9277)" style="paint-order:normal"/><circle cx="96.357" cy="160.62" r="96.375" fill="#121212" style="paint-order:normal"/></g></svg>
)rawliteral";