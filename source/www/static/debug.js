var init = true;
var container, camera, scene, renderer;
const PITCH = 1;
const ROLL = 2;
const YAW = 3;
const SCALE = 0.01;
const ROTOFFX = -Math.PI / 2;
const STR  = 0;
const PREV = 1;
const POSX = 2;
const POSY = 3;
const POSZ = 4;
const ROTX = 5;
const ROTY = 6;
const ROTZ = 7;
const AXIS = 8;
const SCLX = 9;
const SCLY = 10;
const SCLZ = 11;
const OFFX = 12;
const OFFY = 13;
const OFFZ = 14;
const MESH = 15; // NOTE: Must be at the end
var names = [
  "hip-pitch-left",
  "hip-pitch-right",
  "knee-pitch-left",
  "knee-pitch-right",
  "ankle-pitch-left",
  "ankle-pitch-right",
  "ankle-roll-left",
  "ankle-roll-right"
];
var objs = [];
objs[names[0]] = [
  "static/stl/thigh-left.scad.stl", // Location of file
  "",                               // Previous joint
  0.5, 0.5, 0.25,                   // Offset
  0, 0, 0,                          // Rotate
  PITCH,                            // Rotation axis
  SCALE, SCALE, SCALE,              // Scaling
  -50, 0, -55                       // Rotation point
];
objs[names[1]] = [
  "static/stl/thigh-right.scad.stl",
  "",
  -0.5, 0.5, 0.25,
  0, 0, 0,
  PITCH,
  SCALE, SCALE, SCALE,
  50, 0, -55
];
objs[names[2]] = [
  "static/stl/shin-left.scad.stl",
  names[0],
  objs[names[0]][POSX] + 0.01, objs[names[0]][POSY] - 1, objs[names[0]][POSZ] - 0.25,
  0, 0, 0,
  PITCH,
  SCALE, SCALE, SCALE,
  -50, 0, -65
];
objs[names[3]] = [
  "static/stl/shin-right.scad.stl",
  names[1],
  objs[names[1]][POSX] - 0.01, objs[names[1]][POSY] - 1, objs[names[1]][POSZ] - 0.25,
  0, 0, 0,
  PITCH,
  SCALE, SCALE, SCALE,
  50, 0, -65
];
objs[names[4]] = [
  "static/stl/ankle-left.scad.stl",
  names[2],
  objs[names[2]][POSX], objs[names[2]][POSY] - 1, objs[names[2]][POSZ],
  0, 0, 0,
  PITCH,
  SCALE, SCALE, SCALE,
  -55, 35, -45
];
objs[names[5]] = [
  "static/stl/ankle-right.scad.stl",
  names[3],
  objs[names[3]][POSX], objs[names[3]][POSY] - 1, objs[names[3]][POSZ],
  0, 0, 0,
  PITCH,
  SCALE, SCALE, SCALE,
  55, 35, -45
];
objs[names[6]] = [
  "static/stl/foot-left.scad.stl",
  names[4],
  objs[names[4]][POSX], objs[names[4]][POSY] - 0.5, objs[names[4]][POSZ] - 0.35,
  0, 0, 0,
  ROLL,
  SCALE, SCALE, SCALE,
  -55, 0, -35
];
objs[names[7]] = [
  "static/stl/foot-right.scad.stl",
  names[5],
  objs[names[5]][POSX], objs[names[5]][POSY] - 0.5, objs[names[5]][POSZ] - 0.35,
  0, 0, 0,
  ROLL,
  SCALE, SCALE, SCALE,
  55, 0, -35
];

/**
 * update()
 *
 * The main update loop to keep the browser up to date with the internal
 * configuration of the agent.
 **/
function update(){
  /* TODO: Should check if connection exists. */
  /* If the first time, get template data */
  if(init){
    init = false;
    getConfigTemp();
    getImageTemp();
    initModel();
    animateModel();
    /* Wait at least a second to reload this function */
    setTimeout(update, 1000);
  }else{
    /* TODO: Should check if it is ready. */
    getConfigAll();
    reloadImage();
    getTiming();
    getMotion();
    /* Reload this function */
    setTimeout(update, document.getElementById("poll").value);
  }
}

/**
 * initModel()
 *
 * Initialize the model data.
 **/
function initModel(){
  container = document.getElementById("hardware");
  camera = new THREE.PerspectiveCamera(70, 1, 0.01, 10);
  camera.position.x = -0.5;
  camera.position.y = 0;
  camera.position.z = 4;
  camera.rotation.x = -Math.PI / 16;
  camera.rotation.y = -Math.PI / 16;
  scene = new THREE.Scene();
  /* Load STL files */
  var loader = new THREE.STLLoader();
  for(var i = 0; i < names.length; i++){
    loader.load(objs[names[i]][STR], loaderHelper(names[i]));
  }
  /* Lights */
  scene.add(new THREE.HemisphereLight(0x443333, 0x111122));
  addShadowedLight(1, 1, 1, 0xffffff, 1.35);
  addShadowedLight(0.5, 1, -1, 0xffaa00, 1);
  /* Renderer */
  renderer = new THREE.WebGLRenderer({ antialias: true });
  renderer.setPixelRatio(window.devicePixelRatio);
  renderer.setSize(400, 400)
  renderer.gammaInput = true;
  renderer.gammaOutput = true;
  renderer.shadowMap.enabled = true;
  container.appendChild(renderer.domElement);
  /* Listen to resize events */
  window.addEventListener("resize", resizeModel, false);
}

/**
 * loaderHelper()
 *
 * Loader factory function to keep object index from being lost. This works by
 * cloning the index value when running this function.
 *
 * @param i The index into the object array.
 * @return The function created with this method.
 **/
function loaderHelper(i){
  return function(geometry){
    /* STL */
    var material = new THREE.MeshPhongMaterial({ color: 0x888888, specular: 0x111111, shininess: 200 });
    geometry.applyMatrix(new THREE.Matrix4().makeTranslation(objs[i][OFFX], objs[i][OFFY], objs[i][OFFZ]));
    var mesh = new THREE.Mesh(geometry, material);
    objs[i][MESH] = mesh;
    updateMesh(i);
    mesh.scale.set(objs[i][SCLX], objs[i][SCLY], objs[i][SCLZ]);
    mesh.castShadow = true;
    mesh.receiveShadow = true;
    scene.add(mesh);
    /* Rotation point */
    geometry = new THREE.BoxGeometry(0.15, 0.15, 0.15);
    material = new THREE.MeshNormalMaterial();
    mesh = new THREE.Mesh(geometry, material);
    mesh.applyMatrix(t);
    scene.add(mesh);
  }
}

function updateMesh(i){
  if(objs[i] != undefined && objs[i][MESH] != undefined){
    /* Rotate translation if required */
    var p = new THREE.Matrix4().makeTranslation(objs[i][POSX], objs[i][POSY], objs[i][POSZ]);
    var ro = new THREE.Matrix4().makeRotationX(ROTOFFX);
    var rx = new THREE.Matrix4().makeRotationX(objs[i][ROTX]);
    var ry = new THREE.Matrix4().makeRotationY(objs[i][ROTY]);
    var rz = new THREE.Matrix4().makeRotationZ(objs[i][ROTZ]);
    var t = new THREE.Matrix4();
    t = t.multiply(rx);
    t = t.multiply(ry);
    t = t.multiply(rz);
    t = t.multiply(p);
    t = t.multiply(ro);
    objs[i][MESH].position.set(0, 0, 0);
    objs[i][MESH].rotation.set(0, 0, 0);
    objs[i][MESH].applyMatrix(t);
  }
}

/**
 * addShadowLight()
 *
 * Allow a show light to be added to the scene.
 *
 * @param x X position of the light.
 * @param y Y position of the light.
 * @param z Z position of the light.
 * @param color The colour of the light.
 * @param intensity The intensity of the light.
 **/
function addShadowedLight(x, y, z, color, intensity){
  var directionalLight = new THREE.DirectionalLight(color, intensity);
  directionalLight.position.set(x, y, z);
  scene.add(directionalLight);
  directionalLight.castShadow = true;
  var d = 1;
  directionalLight.shadow.camera.left = -d;
  directionalLight.shadow.camera.right = d;
  directionalLight.shadow.camera.top = d;
  directionalLight.shadow.camera.bottom = -d;
  directionalLight.shadow.camera.near = 1;
  directionalLight.shadow.camera.far = 4;
  directionalLight.shadow.mapSize.width = 1024;
  directionalLight.shadow.mapSize.height = 1024;
  directionalLight.shadow.bias = -0.002;
}

/**
 * resizeModel()
 *
 * Allow the window to be gracefully resized.
 **/
function resizeModel(){
  camera.aspect = 1;
  camera.updateProjectionMatrix();
  renderer.setSize(400, 400);
}

/**
 * animateModel()
 *
 * Animate the model data.
 **/
function animateModel(){
  requestAnimationFrame(animateModel);
  for(var i = 0; i < names.length; i++){
    updateMesh(names[i]);
  }
  renderer.render(scene, camera);
}

/**
 * getMotion()
 *
 * Get the current motion values.
 *
 * @param data The current raw motion data.
 **/
function getMotion(data){
  /* Check if we are being called back with data */
  if(getMotion.arguments.length <= 0){
    get("/json/motion", getMotion);
  }else{
    var o = JSON.parse(data);
    var p = getKeyValuePairs(o, "");
    for(var i in p){
      if(objs[p[i][0]] != undefined){
        if(objs[p[i][0]][AXIS] = PITCH){
          objs[p[i][0]][ROTX] = p[i][1];
        }
        if(objs[p[i][0]][AXIS] = ROLL){
          objs[p[i][0]][ROTY] = p[i][1];
        }
        if(objs[p[i][0]][AXIS] = YAW){
          objs[p[i][0]][ROTZ] = p[i][1];
        }
      }
    }
    for(var i = 0; i < names.length; i++){
      /* Copy rotation from previous joint */
      if(objs[names[i]][PREV].length > 0){
        //objs[names[i]][ROTX] += objs[objs[names[i]][PREV]][ROTX];
        //objs[names[i]][ROTY] += objs[objs[names[i]][PREV]][ROTY];
        //objs[names[i]][ROTZ] += objs[objs[names[i]][PREV]][ROTZ];
      }
    }
    delete data;
  }
}

/**
 * getTiming()
 *
 * Get the current timing values.
 *
 * @param data The current raw timing data.
 **/
function getTiming(data){
  /* Check if we are being called back with data */
  if(getTiming.arguments.length <= 0){
    get("/json/timing", getTiming);
  }else{
    var o = JSON.parse(data);
    var p = getKeyValuePairs(o, "");
    var e = document.getElementById("timing");
    var a = [ "" ];
    e.innerHTML = "";
    for(var i in p){
      var c = 0;
      var t = p[i] + "";
      var z = t.indexOf('.');
      while(z >= 0){
        c++;
        z = t.indexOf('.', ++z);
      }
      if(c > 0){
        e.innerHTML += "&nbsp;&nbsp;".repeat(c) + t + "<br>";
      }else{
        e.innerHTML = t + "<br>" + e.innerHTML;
      }
    }
    delete data;
  }
}

/**
 * reloadImage()
 *
 * Reload the image from the camera.
 **/
function reloadImage(){
  var s = document.getElementById("image-type");
  var i = document.getElementById("camera");
  delete i.src;
  i.src = "/vision/image/" + s.options[s.selectedIndex].value + "?" + Date.now();
}

/**
 * getImageTemp()
 *
 * Get the image properties.
 *
 * @param data The current raw image data.
 **/
function getImageTemp(data){
  /* Check if we are being called back with data */
  if(getImageTemp.arguments.length <= 0){
    get("/vision/options", getImageTemp);
  }else{
    var o = JSON.parse(data);
    var s = document.getElementById("image-type");
    for(var x = 0; x < o.types.length; x++){
      var opt = document.createElement("option");
      opt.value = o.types[x].type;
      opt.innerHTML = o.types[x].type;
      s.appendChild(opt);
    }
    delete data;
  }
}

/**
 * saveConfigAll()
 *
 * Tell the server to save the config.
 *
 * @param data The current raw configuration data.
 **/
function saveConfigAll(data){
  /* Check if we are being called back with data */
  if(saveConfigAll.arguments.length <= 0){
    get("/json/config/save", saveConfigAll);
  }else{
    /* TODO: Let the user know it saved. */
    delete data;
  }
}

/**
 * setConfigAll()
 *
 * Send the changed values to the server and update the form to reflect the
 * saved values.
 **/
function setConfigAll(){
  var data = {};
  /* Add elements to the JSON object */
  var elems = document.getElementsByClassName("edit");
  for(e in elems){
    if(elems[e].nodeName == "TR"){
      data[elems[e].id] = elems[e].childNodes[1].childNodes[0].value;
    }
  }
  /* Send them off */
  post("/json/config/update", data);
}

/**
 * getConfigAll()
 *
 * Get the snapshot on the entire configuration file and spit the values out
 * somewhere appropriately.
 *
 * @param data The current raw configuration data.
 **/
function getConfigAll(data){
  /* Check if we are being called back with data */
  if(getConfigAll.arguments.length <= 0){
    get("/json/config/all", getConfigAll);
  }else{
    var o = JSON.parse(data);
    var p = getKeyValuePairs(o, "");
    for(var i in p){
      var tr = document.getElementById(p[i][0]);
      if(tr != null){
        /* Make sure the user didn't edit it */
        if(tr.childNodes[1].childNodes[0].name != "" &&
          tr.childNodes[1].childNodes[0].name != tr.childNodes[1].childNodes[0].value){
          tr.classList.add("edit");
        }else{
          tr.childNodes[1].childNodes[0].value = p[i][1];
        }
        tr.childNodes[1].childNodes[0].name = p[i][1];
      }else{
        alert("Failed to place value for '" + p[i][0] + "'");
      }
    }
    delete data;
  }
}

/**
 * getConfigTemp()
 *
 * Get a snapshot of the entire template and slit the values out somewhere
 * appropriately.
 *
 * @param data The current raw configuration data.
 **/
function getConfigTemp(data){
  /* Check if we are being called back with data */
  if(getConfigTemp.arguments.length <= 0){
    get("/json/config/temp", getConfigTemp);
  }else{
    var t = document.createElement("table");
    var tb = document.createElement("tbody");
    var tr = document.createElement("tr");
    var td;
    /* Create the table header */
    var th = document.createElement("th");
    th.innerHTML = "Name";
    tr.appendChild(th);
    th = document.createElement("th");
    th.innerHTML = "Value";
    tr.appendChild(th);
    th = document.createElement("th");
    th.innerHTML = "Min";
    tr.appendChild(th);
    th = document.createElement("th");
    th.innerHTML = "Max";
    tr.appendChild(th);
    th = document.createElement("th");
    th.innerHTML = "Type";
    tr.appendChild(th);
    tb.appendChild(tr);
    var o = JSON.parse(data);
    var p = getKeyValuePairs(o, "");
    /* Load in template values, creating rows where needed */
    var prev = "";
    for(var i in p){
      /* Find the ID of variable */
      var n = p[i][0].substring(0, p[i][0].lastIndexOf("."));
      /* Find the input field, otherwise create one */
      tr = prev;
      /* NOTE: This is a massive hack and relies on JSON being grouped. */
      if(prev.id != n){
        tr = document.createElement("tr");
        tr.setAttribute("id", n);
        td = document.createElement("td");
        td.innerHTML = n;
        tr.appendChild(td);
        for(var x = 0; x < 4; x++){
          td = document.createElement("td");
          td.appendChild(document.createElement("input"));
          tr.appendChild(td);
        }
        tb.appendChild(tr);
      }
      var s = p[i][0].substring(p[i][0].lastIndexOf(".") + 1);
      switch(s){
        case "type" :
          tr.childNodes[1].childNodes[0].classList.add("value");
          tr.childNodes[1].childNodes[0].type = "text";
          tr.childNodes[2].childNodes[0].classList.add("value");
          tr.childNodes[2].childNodes[0].classList.add("read");
          tr.childNodes[2].childNodes[0].type = "text";
          tr.childNodes[2].childNodes[0].readOnly = true;
          tr.childNodes[3].childNodes[0].classList.add("value");
          tr.childNodes[3].childNodes[0].classList.add("read");
          tr.childNodes[3].childNodes[0].type = "text";
          tr.childNodes[3].childNodes[0].readOnly = true;
          tr.childNodes[4].childNodes[0].classList.add("value");
          tr.childNodes[4].childNodes[0].classList.add("read");
          tr.childNodes[4].childNodes[0].type = "text";
          tr.childNodes[4].childNodes[0].readOnly = true;
          tr.childNodes[4].childNodes[0].value = p[i][1];
          break;
        case "default" :
          tr.childNodes[1].childNodes[0].value = p[i][1];
          break;
        case "min" :
          tr.childNodes[2].childNodes[0].value = p[i][1];
          break;
        case "max" :
          tr.childNodes[3].childNodes[0].value = p[i][1];
          break;
        default :
          alert("Failed to place key '" + s + "'");
      }
      prev = tr;
    }
    t.appendChild(tb);
    var e = document.getElementById("config");
    e.innerHTML = "";
    e.appendChild(t);
    delete data;
  }
}

/**
 * getKeyValuePairs()
 *
 * Recursive function to find all key value pairs and generate an array from a
 * JSON object.
 *
 * @param obj The object to be traversed.
 * @param path Current path for this object.
 * @return An array of key value pairs.
 **/
function getKeyValuePairs(obj, path){
  var pairs = [];
  for(var o in obj){
    if(typeof obj[o] == "object"){
      /* Still further to search */
      var d = getKeyValuePairs(obj[o], path + "" + o + ".");
      for(var i in d){
        pairs.push(d[i]);
      }
    }else{
      pairs.push([path + "" + o + "", obj[o]]);
    }
  }
  console.log(pairs);
  return pairs;
}

/**
 * post()
 *
 * Sends a request to the specified URL from a form. This will change the
 * window location. Source: https://stackoverflow.com/a/133997/2847743
 *
 * @param path Path to send the post request to.
 * @param params The parameters to add to the URL.
 * @param method The method to use on the form.
 **/
function post(path, params, method){
  /* Set method to post by default if not specified */
  method = method || "post";
  /* The rest of this code assumes you are not using a library */
  /* It can be made less wordy if you use one */
  var form = document.createElement("form");
  form.setAttribute("method", method);
  form.setAttribute("action", path);
  for(var key in params){
    if(params.hasOwnProperty(key)){
      var hiddenField = document.createElement("input");
      hiddenField.setAttribute("type", "hidden");
      hiddenField.setAttribute("name", key);
      hiddenField.setAttribute("value", params[key]);
      form.appendChild(hiddenField);
    }
  }
  document.body.appendChild(form);
  form.submit();
}

/**
 * get()
 *
 * Asynchronous get request to a URL. Source:
 * https://stackoverflow.com/a/4033310/2847743
 *
 * @param path Path to send the get request to.
 * @param callback The method to be called once the data is retrieved.
 **/
function get(path, callback){
  var xmlHttp = new XMLHttpRequest();
  xmlHttp.onreadystatechange = function(){
    if(xmlHttp.readyState == 4 && xmlHttp.status == 200){
      callback(xmlHttp.responseText);
    }
  }
  /* True for asynchronous */
  xmlHttp.open("GET", path, true);
  xmlHttp.send(null);
}
