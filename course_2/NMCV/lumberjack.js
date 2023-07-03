if (tick == 0) {
    if (typeof (sceneexist) == 'undefined') {
        OpenCanvas('wCanvas', WC = 520, HC = 400);
        var scene, camera, renderer; CreateScene(WC, HC);
        X=0; Y=0; Z=0; W=10; limit=0; flag = false;
 
        removeButtons();
 
        Robot = DrawRobot();
        Robot.position.set(X, Y, Z);
        Robot.scale.set(W, W, W);
        scene.add(Robot);
 
        Field = DrawField();
        Field.position.set(X, Y, Z);
        Field.scale.set(W, W, W);
        scene.add(Field);
        
        Pine = DrawPine();
        Pine.scale.set(W, W, W);
        Pine.position.set(X, Y, Z);
        scene.add(Pine);
        
        Birch = DrawBirch();
        Birch.scale.set(W, W, W);
        Birch.position.set(X, Y, Z);
        scene.add(Birch);
        
        Lawn = DrawLawn();
        Lawn.scale.set(W, W, W);
        Lawn.position.set(X,Y,Z);
        scene.add(Lawn);
        
        Sky = DrawSky()
        Sky.scale.set(W, W, W);
        Sky.position.set(X,Y,Z);
        scene.add(Sky);
        
        F = true;
        render();
    }
}
F=true;
 
restart(20);
 
// вывод текущего тика
puts(tick);
 
function render(){
    // двжиение робота
    moveRobot();
    requestAnimationFrame(render);
    controls.update();
    renderer.render(scene,camera);
}
 
// создание поля
function DrawField(){
    loader = new THREE.TextureLoader();
    
    field_texture = loader.load("http://livelab.spb.ru/labs/files/trava.jpg");
    field_texture.repeat.set(4, 4);
    field_texture.wrapS = field_texture.wrapT = THREE.RepeatWrapping;
    field_texture.anisotropy = 16;
    var material = new THREE.MeshBasicMaterial( {color: 0x95DDA4, side: THREE.DoubleSide, map : field_texture} );
    var fieldGeom = new THREE.BoxGeometry(13, 13, 0.02);
    var field = new THREE.Mesh(fieldGeom, material);
 
    var out = new THREE.Object3D();
    out.add(field); 
 
    return out;
}
 
 
function DrawSky() {
    var skyGeo = new THREE.SphereGeometry(40, 10, 10); 
    var loader  = new THREE.TextureLoader();
    
    texture = loader.load( "http://livelab.spb.ru/labs/files/SkyDomeTexture3.jpg" );
    texture.wrapS = THREE.RepeatWrapping;
    texture.wrapT = THREE.RepeatWrapping;
    texture.repeat.set(6, 3);
    var material = new THREE.MeshBasicMaterial({ 
      map: texture
    });
    var sky = new THREE.Mesh(skyGeo, material);
    sky.material.side = THREE.BackSide;
    sky.rotation.x = (PI/2);
    var out=new THREE.Object3D;
    out.add(sky);
    return out;
}
 
function DrawLawn(){
    const x = 30; // ширина
    const y = 30; // глубина
    const c = 300; // количество кустиков травы
    var WS = 0.4;
    var lawn = new THREE.Object3D();
 
    // ПРОПЛЕШИНА
    // координаты центра проплешины
    var propleshina_x = 0; 
    var propleshina_y = 0;
    // габариты проплешины
    var propleshina_scale_x = 7;
    var propleshina_scale_y = 5.5;
    
    for(var i = 0; i < c; i++){
        var grass = DrawGrass();
        var nx = x * (Math.random() - 0.5);
        var ny = y * (Math.random() - 0.5);
        // ПРОПЛЕШИНА
        if(nx <= propleshina_x + propleshina_scale_x/2 && 
            nx >= propleshina_x - propleshina_scale_x/2 &&
            ny <= propleshina_y + propleshina_scale_y/2 &&
            ny >= propleshina_y - propleshina_scale_y/2){
                continue;
            }
 
        grass.position.set(nx, ny, 0);
        grass.rotation.set(0,0, Math.random() * PI/2);
        lawn.add(grass);
    }
    // упаковка
    lawn.scale.set(WS, WS, WS);
    var out = new THREE.Object3D();
    out.add(lawn);
    return out;
}
 
function DrawGrass(){
    if(typeof loader == 'undefined'){
        loader = new THREE.TextureLoader();
    }
    if(typeof grass_texture == 'undefined'){
        grass_texture = loader.load("https://i.postimg.cc/3JGNfNnk/grass.png");
    }
    var grass = new THREE.Object3D();
    
    var geometry = new THREE.PlaneGeometry( 3, 2 );
    var material = new THREE.MeshBasicMaterial( {color: 0xffffff, side: THREE.DoubleSide, map : grass_texture, alphaTest: 0.7} );
    var plane = new THREE.Mesh( geometry, material );
    plane.rotateX(PI/2);
    var h = 0.9;
    plane.position.set(0,0,h);
    
    var plane2 = plane.clone();
    plane2.rotateY(PI/2);
    plane2.position.set(0,0,h);
    grass.add( plane );
    grass.add( plane2 );
    // упаковка
    var WS = 0.8 + 0.2 * Math.random();
    grass.scale.set(WS, WS, WS);
    var out = new THREE.Object3D();
    out.add(grass);
    return out;
}
 
function DrawPine(){
    if(typeof loader == 'undefined'){
        loader = new THREE.TextureLoader();
    }
    if(typeof pine_texture == 'undefined'){
        pine_texture = loader.load("https://i.postimg.cc/SxQ7S17c/pine.png");
    }
    var pine = new THREE.Object3D();
    var loader = new THREE.TextureLoader();
    var geometry = new THREE.PlaneGeometry(10, 20);
    var material = new THREE.MeshBasicMaterial( {color: 0xffffff, side: THREE.DoubleSide, map : pine_texture, alphaTest: 0.95} );
    var plane = new THREE.Mesh( geometry, material );
 
    plane.rotateX(PI/2);
    var h = 9.9;
    plane.position.set(0,0,h);
 
    var plane2 = plane.clone();
    plane2.rotateY(PI/2);
    plane2.position.set(-0.6,0.6,h);
 
    var plane3 = plane.clone();
    plane3.scale.set(-1,1,1);
    plane3.rotateY(PI/4);
    plane3.position.set(-1.1,-0.4,h);
 
    var plane4 = plane.clone();
    plane4.scale.set(-1,1,1);
    plane4.rotateY(-PI/4);
    plane4.position.set(-1.1,0.5,h);
 
    pine.add( plane );
    pine.add( plane2 );
    pine.add( plane3 );
    pine.add( plane4 );
    
    // упаковка
    var WS = 0.27 + 0.067 * Math.random();
    pine.scale.set(WS, WS, WS);
    pine.position.set(3, -2, 0);
    var out = new THREE.Object3D();
    out.add(pine);
    return out;
}
 
function DrawBirch(){
    if(typeof loader == 'undefined'){
        loader = new THREE.TextureLoader();
    }
    if(typeof birch_texture == 'undefined'){
        birch_texture = loader.load("https://i.postimg.cc/YCXNhNbZ/birch.png");
    }
    var birch = new THREE.Object3D();
    var geometry = new THREE.PlaneGeometry( 10, 15 );
    var material = new THREE.MeshBasicMaterial( {
        color: 0xffffff, 
        side: THREE.DoubleSide, 
        map : birch_texture, 
        alphaTest: 0.85} );
        
    var plane = new THREE.Mesh( geometry, material );
    plane.rotateX(PI/2);
    var h = 6.8;
    plane.position.set(0,0,h);
    
    var plane2 = plane.clone();
    plane2.rotateY(PI/2);
    plane2.position.set(-0.8,0.6,h);
    
    var plane3 = plane.clone();
    plane3.scale.set(-1,1,1);
    plane3.rotateY(PI/4);
    plane3.position.set(-1.1,-0.7,h);
 
    var plane4 = plane.clone();
    plane4.scale.set(-1,1,1);
    plane4.rotateY(-PI/4);
    plane4.position.set(-1.1,0.5,h);
    
    birch.add( plane );
    birch.add( plane2 );
    birch.add( plane3 );
    birch.add( plane4 );
    // Упаковка
    var WS = 0.27 + 0.067 * Math.random();
    birch.scale.set(WS, WS, WS);
    birch.position.set(-3, 3, 0);
    var out = new THREE.Object3D();
    out.add(birch);
    return out;
}
 
 
// алгоритм движения робота
function moveRobot() {
    if (F) { 
        F=false; 
        switch(true) {
            case tick < 150:
            Robot.position.y -= 0.02*W;
            doAnimation();
            break;
            
            case tick === 150:
            Robot.rotateZ(-PI/2); 
            break;
            
            case tick < 300: 
            Robot.position.x -= 0.02*W; 
            doAnimation();
            break;
                      
            case tick === 300:
            Robot.rotateZ(-PI/2); 
            break;
            
            case tick < 500: 
            Robot.position.y += 0.02*W;
            doAnimation();
            break; 
            
            case tick === 500: 
            Robot.rotateZ(-PI/2);
            break; 
            
            case tick < 700:
            Robot.position.x += 0.02*W;
            doAnimation();
            break
            
            case tick == 700:
            window.location.reload();
        }
    }
 
}
 
// анимация ног
function doAnimation() {
    if (!flag){
        if (limit != 0.2){
            limit += 0.05;
        } else {
            flag = true;
            } 
        } else {
        if (limit != -0.2){
            limit -= 0.05; 
        } else {
            flag = false;
            }
    }
    
robotLeftLeg.rotation.z=limit;
robotRightLeg.rotation.z=-limit;
robotLeftLeg.position.y=(0+0.18*limit)*W;
robotRightLeg.position.y=(0-0.18*limit)*W;
}
 
 
// отрисовка робота
function DrawRobot(){
    Robot = new THREE.Group();
 
    // materials
    let greyColor = new THREE.MeshStandardMaterial( {color: 0xBEBEBE} );
    let brownColor = new THREE.MeshLambertMaterial({color: 0x4f2d27});
    let whiteColor = new THREE.MeshLambertMaterial({color: 0xFFFFFF });
    let darkGreyColor = new THREE.MeshStandardMaterial({color: 0x494D4E});
    let blackColor = new THREE.MeshLambertMaterial({color: 0x000000});
    let redColor = new THREE.MeshLambertMaterial({color: 0xFF0000});
    let chestMaterial = new THREE.MeshBasicMaterial( {color: 0x494D4E, opacity: 0.6, transparent: true} );
 
    // axe
    let axeHandleGeom = new THREE.CylinderGeometry(0.1, 0.1, 6);
    let axeHandle = new THREE.Mesh(axeHandleGeom, brownColor);
    axeHandle.position.set(0.65, 0.2, 4);
    axeHandle.rotateZ(PI/4.4);
    axeHandle.rotateX(PI/4);
    
    let axeEdgeGeom = new THREE. BoxGeometry(1.2, 0.6, 0.1);
    let axeEdge = new THREE.Mesh(axeEdgeGeom, greyColor);
    axeEdge.position.set(-1.05, 1.3, 5.95);
    axeEdge.rotateZ(PI/4.4);
    axeEdge.rotateX(PI/4);
 
    Axe = new THREE.Group();
    Axe.add(axeHandle, axeEdge);
 
    // hat
    let spireHatGeom = new THREE.CylinderGeometry(0.1, 0.1, 1);
    let spireHat = new THREE.Mesh(spireHatGeom, darkGreyColor);
    spireHat.position.set(0, 0, 7.1);
    spireHat.rotateX(PI/2);
    let circleHatGeom = new THREE.TorusGeometry(0.1, 0.04, 8);
    let circleHat = new THREE.Mesh(circleHatGeom, darkGreyColor);
    circleHat.position.set(0.17, 0, 7.1);
    circleHat.rotateX(PI/2);
    let coneHatGeom = new THREE.ConeGeometry(5, 10, 15, 1, false, 0, 2*PI);
    let coneHat = new THREE.Mesh(coneHatGeom, darkGreyColor);
    coneHat.position.set(0, 0, 6.5)
    coneHat.rotateX(PI/2);
    coneHat.scale.set(0.15,0.15,0.1);
    
    // hat group
    Hat = new THREE.Group();
    Hat.add(coneHat, spireHat, circleHat);
    Hat.position.set(0, 0, -0.8);
 
    // body
    let bodyGeom = new THREE.CylinderGeometry(0.7, 1.1, 3.5, 12, 12);
    let body = new THREE.Mesh(bodyGeom, greyColor);
    body.position.set(0,0,1.2);
    body.rotateX(-PI/2);
    
    // cage
    let chestCageGeom = new THREE.BoxGeometry(0.7, 1, 2);
    let chestCage = new THREE.Mesh(chestCageGeom, chestMaterial);;
    chestCage.position.set(0,-0.8,1.2);
    chestCage.rotateZ(PI/2);
    chestCage.rotateY(-PI/12);
    
    // cage rods
    let rodGeom = new THREE.CylinderGeometry(0.1, 0.1, 2);
    let rod = new THREE.Mesh(rodGeom, darkGreyColor);
    rod.position.set(-0.4,-1, 1.15);
    rod.rotateX(PI/1.7);
    secondRod = rod.clone();
    secondRod.position.set(0,-1, 1.15)
    thirdRod = rod.clone();
    thirdRod.position.set(0.4, -1, 1.15)
    
    // cage plate
    let palteGeom = new THREE.BoxGeometry(1, 0.5, 0.1);
    let plate = new THREE.Mesh(palteGeom, darkGreyColor);
    plate.position.set(0,-1.15, 2.19);
    plate.rotateX(PI/12);
    
    // heart
    let heartGeom = new THREE.SphereBufferGeometry(0.2,10,8);
    let heart = new THREE.Mesh(heartGeom, redColor);
    heart.scale.set(1, 1, 1.5);
    heart.position.set(0, -1, 1.8);
    
    // heart light
    let heartLight = new THREE.Object3D();
    let cap = new THREE.Object3D();
    let mainHeartLight= new THREE.PointLight(0xFF0000, W*5, W/6.65);
    cap.add(mainHeartLight);
    mainHeartLight.position.set(0, -1.5, 1.7);
    heartLight.add(cap);
 
    // Corpus Group
    Corpus = new THREE.Group();
    Corpus.add(body, chestCage, rod, secondRod, thirdRod, plate, heart, heartLight);
 
    // mouth
    let mouthGeom = new THREE.CylinderBufferGeometry(0.48, 0.48, 0.25, 40, 2,false,0,PI/2);
    let mouth = new THREE.Mesh(mouthGeom, whiteColor);
    mouth.position.set(0.05, -0.42, 4.5);
    mouth.scale.set(0.7, 0.5, 1);
    mouth.rotateX(PI/2);
    mouth.rotateY(-PI/4);
    
    // eyebrows
    let eyebrowGeom = new THREE.BoxBufferGeometry(0.25, 0.0625, 0.0625, 40, 2);
    let rightEyebrow = new THREE.Mesh(eyebrowGeom, blackColor);
    rightEyebrow.position.set(0.3,-0.6, 5.65);
    leftEyebrow = rightEyebrow.clone();
    leftEyebrow.position.set(-0.3,-0.6, 5.65);
    leftEyebrow.rotateY(-PI/6);
    
    // pupils
    let pupilGeom = new THREE.CylinderBufferGeometry(0.0625, 0.0625, 0.0625, 40, 2);
    let rightPupil = new THREE.Mesh(pupilGeom, blackColor);
    rightPupil.position.set(-0.35,-0.69, 5.4)
    rightPupil.scale.set(1,1,1.1);
    leftPupil = rightPupil.clone();
    leftPupil.position.set(0.25,-0.69, 5.4);
    
    // eyes
    let eyeGeom = new THREE.CylinderBufferGeometry(0.25, 0.25, 0.25,40,2);
    let leftEye = new THREE.Mesh(eyeGeom, whiteColor);
    leftEye.position.set(-0.3,-0.6, 5.4);
    leftEye.scale.set(0.65, 0.65, 0.65);
    rightEye =leftEye.clone();
    rightEye.position.set(0.3,-0.6, 5.4)
    
    let EyeGroup = new THREE.Group();
    EyeGroup.add(leftEye, rightEye);
 
    // nose
    let noseGeom = new THREE. SphereBufferGeometry(0.25, 0.25, 0.25);
    let nose = new THREE.Mesh(noseGeom, darkGreyColor);
    nose.position.set(0, -0.7, 5);
    nose.scale.set(0.5, 0.5, 0.5);
 
    // head
    let headGeom = new THREE.CylinderGeometry(0.5,0.6,1.5);
    let head = new THREE.Mesh(headGeom, greyColor);
    head.position.set(0,-0.2,5);
    head.rotateX(PI/2); 
    
    headGroup = new THREE.Group();
    headGroup.add(head,leftEye,rightEye, leftPupil, rightPupil, rightEyebrow, leftEyebrow, mouth, nose);
    headGroup.position.set(0,0.2,-0.8);
 
    // neck
    let neckMainGeom = new THREE.CylinderGeometry(0.2,0.3,2,10);
    let neckMain = new THREE.Mesh(neckMainGeom, greyColor);
    neckMain.position.set(0,0,3.5);
    neckMain.rotateX(-PI/2);
    let neckRingGeom = new THREE.TorusGeometry(0.5, 0.2, 16);
    let neckRing = new THREE.Mesh(neckRingGeom, greyColor);
    neckRing.position.set(0, 0, 3);
    
    // neck group
    neck = new THREE.Group();
    neck.add(neckMain,neckRing);
    
    // shoulders
    let shoulderGeom = new THREE.CylinderGeometry(0.2,0.2,1.3,10);
    let leftShoulder= new THREE.Mesh(shoulderGeom,greyColor);
    leftShoulder.rotateX(PI/2);
    leftShoulder.rotateZ(-PI/3);
    leftShoulder.position.set(-1.5,0,2);
    rightShoulder = leftShoulder.clone();
    rightShoulder.rotateZ(2*PI/3);
    rightShoulder.position.set(1.5,0,2);
    
    // joints
    let jointGeom = new THREE.SphereBufferGeometry(0.2,10,8);
    let leftJoint = new THREE.Mesh(jointGeom,greyColor);
    leftJoint.position.set(-2.1,0,1.63);
    rightJoint = leftJoint.clone();
    rightJoint.position.set(2.1,0,1.63);
 
    // shoulder rings
    let ShoulderRingGeom = new THREE.TorusGeometry(0.3, 0.1, 16);
    let rightShoulderRing = new THREE.Mesh(ShoulderRingGeom, greyColor);
    rightShoulderRing.position.set(1.05, 0, 2.2);
    rightShoulderRing.rotateY(-PI/2);
    leftShoulderRing = rightShoulderRing.clone();
    leftShoulderRing.position.set(-1.05, 0, 2.2);
    
    // hands
    leftHand = new THREE.Group();
    leftHand.add(leftShoulder,leftJoint);
    rightHand = new THREE.Group();
    rightHand.add(rightShoulder,rightJoint);
    predleftShoulder = rightShoulder.clone();
    predrightShoulder = leftShoulder.clone();
    predleftShoulder.position.set(-1.5,0,1.3);
    predrightShoulder.position.set(2,-0.6,1.88);
    predrightShoulder.rotateX(PI/2);
    predrightShoulder.rotateZ(PI/6);
    
    // palms
    let palmGeom = new THREE.SphereBufferGeometry(0.2,10,8);
    let palm = new THREE.Mesh(palmGeom,greyColor);
    palm.position.set(1.9, -1.1, 2.12);
    palm.scale.set(1,1,1.8);
    palm.rotateY(PI/2);
    palmL= palm.clone();
    palmL.position.set(-1,0,0.8);
 
    // arm groups
    rightArm = new THREE.Group();
    rightArm.add(predrightShoulder,palm, rightShoulderRing);
    leftArm = new THREE.Group();
    leftArm.add(predleftShoulder, palmL, leftShoulderRing);
    
    // legs
    let legGeom = new THREE.CylinderGeometry(0.3,0.2,3,10);
    let leftLeg = new THREE.Mesh(legGeom,greyColor);
    leftLeg.position.set(-0.4,0,-1.4);
    leftLeg.rotateX(PI/2);
    rightLeg=leftLeg.clone();
    rightLeg.position.set(0.4,0,-1.4);
 
    // feet
    leftFoot = palm.clone();
    leftFoot.position.set(-0.45,-0.13,-2.8);
    leftFoot.scale.set(1,1,2);
    leftFoot.rotateX(PI/2);
    leftFoot.rotateY(-PI/6);    
    rightFoot = leftFoot.clone();
    rightFoot.position.set(0.45,-0.13,-2.8);
    rightFoot.rotateY(PI/3);
    leftFoot.rotateY(PI/3);
    
    // leg groups
    robotLeftLeg = new THREE.Group();
    robotLeftLeg.add(leftLeg,leftFoot);
    robotLeftLeg.position.set(0,0,-0.5);
    robotRightLeg = new THREE.Group();
    robotRightLeg.add(rightLeg,rightFoot);
    robotRightLeg.position.set(0,0,-0.5);
    
    // robot assembling
    Robot.add(Axe);
    Robot.add(Hat);
    Robot.add(Corpus);
    Robot.add(EyeGroup);
    Robot.add(headGroup);
    Robot.add(neck);
    Robot.add(leftHand);
    Robot.add(rightHand);
    Robot.add(leftArm);
    Robot.add(rightArm);
    Robot.add(robotLeftLeg);
    Robot.add(robotRightLeg);
 
     
    Robot.receiveShadow = true;
 
    // Юстировка размера и позиции
    let WS=0.2;
    Robot.scale.set(WS,WS,WS);
    Robot.position.set(0, 0, 0.7);
    
    let out = new THREE.Object3D();
    out.add(Robot);
 
    return out;
}
 
function CreateScene(WC,HC) {
    if (typeof(sceneexist)=='undefined') { 
        sceneexist = true;
        scene = new THREE.Scene();
        scene.background = new THREE.Color(0x444488 );
        camera = new THREE.PerspectiveCamera(30, WC/HC, 1, 1000);
        camera.position.x = 0;
        camera.position.y = -145;
        camera.position.z = 45;
        camera.lookAt( scene.position );
        renderer = new THREE.WebGLRenderer({
        alpha: true, antialias: true});
 
        renderer.setPixelRatio( window.devicePixelRatio );
        document.getElementById("wCanvas").appendChild(renderer.domElement);
        renderer.setSize(WC,HC);
 
        controls = new THREE.TrackballControls( camera,renderer.domElement );
        controls.rotateSpeed = 1.0;
        controls.zoomSpeed = 1.2;
        controls.panSpeed = 0.8;
        controls.noZoom = false;
        controls.noPan = true;
        controls.staticMoving = false;
        controls.dynamicDampingFactor = 0.2;
 
        scene.add( new THREE.AmbientLight( 0x555555 ) );
        let directionalLight = new THREE.DirectionalLight( 0xffffff, 1);
        directionalLight.position.set(5,-2,4).normalize();
        scene.add( directionalLight );
        directionalLight.position.set(-5,-2,4).normalize();
        scene.add( directionalLight );
    }
}
 
function removeButtons() {
document.querySelector(`#cal`).remove()
document.querySelector(`#mainFORM > center > table > tbody > tr:nth-child(2) > td > input[type=button]:nth-child(2)`).remove()
}
 
{{html
<!DOCTYPE html>
<head>
<script SRC="http://livelab.spb.ru/x3d/three.min.js"></script>
 <script SRC="http://livelab.spb.ru/x3d/TrackballControls.js"></script>
<script SRC="http://livelab.spb.ru/x3d/OBJLoader.js"></script>
<script SRC="http://livelab.spb.ru/x3d/DDSLoader.js"></script>
<script SRC="http://livelab.spb.ru/x3d/MTLLoader.js"></script>
<input type="button" onClick="window.location.reload()" value="Restart"/>
</head>
html}}