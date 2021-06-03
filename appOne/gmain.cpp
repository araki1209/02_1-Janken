#if 1
#include"libOne.h"
struct DATA {
    //プレイヤーデータ
    int playerGUImage ;
    int playerCHOKIImage;
    int playerPAImage ;
    int pcGUImage ;
    int pcCHOKIImage;
    int pcPAImage ;
    int heartImage ;
    int GU=0;
    int CHOKI =1;
    int PA=2;
    int playerHand;
    int playerImage;
    float playerPx;
    float playerPy;
    float playerAngle;
    float playerR;
    float playerG;
    float playerB;
    int playerLife;
    //ｐｃデータ
    int pcHand;
    int pcImage;
    float pcPx;
    float pcPy;
    float pcAngle;
    float pcR;
    float pcG;
    float pcB;
    int pcLife;
    //勝ち負け文字
    float resultPx;
    float resultPy;
    float resultSize;
    //状態の切り替え
    int INIT=0;
    int PLAY = 1;
    int RESULT=2;
    int state=INIT;
};

void loadImges(struct DATA* d) {
   d->playerGUImage = loadImage("assets\\playerGu.png");
   d->playerCHOKIImage = loadImage("assets\\playerChoki.png");
   d->playerPAImage = loadImage("assets\\playerPa.png");
   d->pcGUImage = loadImage("assets\\pcGu.png");
   d->pcCHOKIImage = loadImage("assets\\pcChoki.png");
   d->pcPAImage = loadImage("assets\\pcPa.png");
   d->heartImage = loadImage("assets\\heart.png");

}
void init(struct DATA* d) {
  d->playerHand = d->GU;
  d->playerImage = d->playerGUImage;
  d->playerPx = 250;
  d->playerPy = 225;
  d->playerAngle = 0;
  d->playerR = 255;
  d->playerG = 255;
  d->playerB = 255;
  d->playerLife = 3;
    //ｐｃデータ
  d->pcHand = d->GU;
  d->pcImage = d->pcGUImage;
  d->pcPx = 550;
  d->pcPy = 225;
  d->pcAngle = 0;
  d->pcR = 255;
  d->pcG = 255;
  d->pcB = 255;
  d->pcLife = 3;
    //勝ち負け文字
  d->resultPx = 225;
  d->resultPy = 320;
  d->resultSize = 0;
    //ゲームステート切り替え
  d->state = d->PLAY;
}
void play(struct DATA* d) {
    if (isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {
        //プレイヤーの手を決める
        if (isTrigger(KEY_A)) { d->playerHand = d->GU; }
        else if (isTrigger(KEY_S)) { d->playerHand = d->CHOKI; }
        else if (isTrigger(KEY_D)) { d->playerHand = d->PA; }
        //プレイヤーの画像を切り替える
        if (d->playerHand == d->GU) { d->playerImage = d->playerGUImage; }
        else if (d->playerHand == d->CHOKI) { d->playerImage = d->playerCHOKIImage; }
        else if (d->playerHand == d->PA) {d->playerImage = d->playerPAImage; }
        //ｐｃの手を決める
        d->pcHand = random() % 3;
        //ｐｃの画像を切り替える
        if (d->pcHand == d->GU) { d->pcImage = d->pcGUImage; }
        else if (d->pcHand == d->CHOKI) { d->pcImage = d->pcCHOKIImage; }
        else if (d->pcHand == d->PA) { d->pcImage = d->pcPAImage; }
        //勝ち負けを判定し、色を変える
        if (d->playerHand == d->pcHand) {//あいこ
            d->playerR = 255; d->playerG = 255; d->playerB = 255;
            d->pcR = 255; d->pcG = 255; d->pcB = 255;
        }
        else if ((d->playerHand + 1) % 3 == d->pcHand) {//プレイヤーの勝ち
            d->playerR = 255; d->playerG = 200; d->playerB = 200;
            d->pcR = 255; d->pcG = 255; d->pcB = 255;
            d->pcLife--;
        }
        else { //ｐｃの勝ち
            d->playerR = 255; d->playerG= 255; d->playerB = 255;
            d->pcR = 255; d->pcG = 200; d->pcB = 200;
            d->playerLife--;
        }
        //ゲームステートの切り替え
        if (d->playerLife == 0 ||d->pcLife == 0) {
            d->state = d->RESULT;
        }
    }
}
void result(struct DATA* d) {
        //ｐｃの負け
        if (d->pcLife == 0) {
            d->pcPy += 1.0f;
            d->pcAngle += -0.005;
        }
        //プレイヤーの負け
        else {
            d->playerPy += 1.0f;
            d->playerAngle += -0.005;
        }
        //勝ち負け文字を拡大する
        if (d->resultSize < 180) {
            d->resultSize += 10.0f;
        }
        if (isTrigger(KEY_SPACE)) {
            d->state = d->INIT;
        }

}
void draw(struct DATA* d) {
    clear(200);
    rectMode(CENTER);
    //プレイヤーの手
    imageColor(d->playerR, d->playerG, d->playerB);
    image(d->playerImage, d->playerPx, d->playerPy, d->playerAngle);
    //pcの手
    imageColor(d->pcR, d->pcG, d->pcB);
    image(d->pcImage, d->pcPx, d->pcPy, d->pcAngle);
    //プレイヤーハート
    imageColor(255, 0, 0);
    for (int i = 0; i < d->playerLife; i++) {
        image(d->heartImage, d->playerPx - 50 + i * 50, d->playerPy - 110);
    }
    //ｐｃハート
    imageColor(255, 0, 0);
    for (int i = 0; i < d->pcLife; i++) {
        image(d->heartImage, d->pcPx - 50 + i * 50, d->pcPy - 110);
    }

    if (d->state == d->RESULT) {
        textSize(d->resultSize);
        if (d->playerLife > 0) {
            fill(255, 0, 0);
            text("勝ち", d->resultPx, d->resultPy);
        }
        else {
            fill(0, 0, 200);
            text("負け", d->resultPx, d->resultPy);
        }
    }
}
#include"libOne.h"
void gmain() {
    //ウィンドウ表示
    window(800, 450);
    struct DATA d;
    //画像の読み込み
    loadImges(&d);
    //メインループ
    while (notQuit) {
        if (d.state == d.INIT) {init(&d);}
        else if (d.state == d.PLAY) { play(&d); }
        else if (d.state == d.RESULT) {result(&d);}
        draw(&d);
    }
}  

    
#else

#include"libOne.h"
void gmain(){
    //ウィンドウ表示
    window(800, 450);
    //画像読み込み
    int playerGuImg    = loadImage("assets\\playerGu.png");
    int playerChokiImg = loadImage("assets\\playerChoki.png");
    int playerPaImg    = loadImage("assets\\playerPa.png");
    int pcGuImg        = loadImage("assets\\pcGu.png");
    int pcChokiImg     = loadImage("assets\\pcChoki.png");
    int pcPaImg        = loadImage("assets\\pcPa.png");
    int heartImg       = loadImage("assets\\heart.png");
    //手の番号を決めておく
    int GU = 0;
    int CHOKI = 1;
    int PA = 2;
    //プレイヤーデータ
    int playerHand;
    int playerImg;
    float playerPx;
    float playerPy;
    float playerAngle;
    float playerR;
    float playerG;
    float playerB;
    int playerLife;
    //ＰＣデータ
    int pcHand;
    int pcImg;
    float pcPx;
    float pcPy;
    float pcAngle;
    float pcR;
    float pcG;
    float pcB;
    int pcLife;
    //勝ち負け文字用
    float resultPx;
    float resultPy;
    float resultSize;
    //状態切り替え
    int INIT   = 0;
    int PLAY   = 1;
    int RESULT = 2;
    int state = INIT;
    //メインループ
    while (notQuit) {
        //データ更新-----------------------------------------------------------
        if (state == INIT) {
            //試合直前初期値設定
            //プレイヤーデータ
            playerHand = GU;
            playerImg = playerChokiImg;
            playerPx = 250;
            playerPy = 225;
            playerAngle = 0;
            playerR = 255;
            playerG = 255;
            playerB = 255;
            playerLife = 3;
            //ＰＣデータ
            pcHand = GU;
            pcImg = pcChokiImg;
            pcPx = 550;
            pcPy = 225;
            pcAngle = 0;
            pcR = 255;
            pcG = 255;
            pcB = 255;
            pcLife = 3;
            //勝ち負け文字
            resultPx = 225;
            resultPy = 320;
            resultSize = 0;
            //ゲームステート切り替え
            state = PLAY;
        }
        else if( state == PLAY ){
            //試合中-----------------------------------------------------------
            //A,S,Dいずれかのキーが押されたら
            if (isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {
                //プレイヤーの手を決める---------------------------------------
                if      (isTrigger(KEY_A)) { playerHand = GU; }
                else if (isTrigger(KEY_S)) { playerHand = CHOKI; }
                else if (isTrigger(KEY_D)) { playerHand = PA; }
                //プレイヤーの画像を切り替える
                if      (playerHand == GU   ) { playerImg = playerGuImg; }
                else if (playerHand == CHOKI) { playerImg = playerChokiImg; }
                else if (playerHand == PA   ) { playerImg = playerPaImg; }
                //ＰＣの手を決める---------------------------------------------
                pcHand = random() % 3;
                //ＰＣの画像を切り替える
                if      (pcHand == GU   ) { pcImg = pcGuImg; }
                else if (pcHand == CHOKI) { pcImg = pcChokiImg; }
                else if (pcHand == PA   ) { pcImg = pcPaImg; }
                //勝ち負け判定し、色を変える-----------------------------------
                if (playerHand == pcHand) {
                    //あいこ
                    playerR = 255; playerG = 255; playerB = 255;
                    pcR = 255; pcG = 255; pcB = 255;
                }
                else if ((playerHand + 1) % 3 == pcHand) {
                    //プレイヤー勝ち
                    playerR = 255; playerG = 200; playerB = 200;
                    pcR = 255; pcG = 255; pcB = 255;
                    pcLife--;
                }
                else {
                    //ＰＣ勝ち
                    playerR = 255; playerG = 255; playerB = 255;
                    pcR = 255; pcG = 200; pcB = 200;
                    playerLife--;
                }
                //ゲームステート切り替え---------------------------------------
                if (playerLife == 0 || pcLife == 0) {
                    state = RESULT;
                }
            }
        }
        else if(state == RESULT){
            //試合終了---------------------------------------------------------
            if (pcLife == 0) {
                //ＰＣ負け
                pcPy += 1.0f;
                pcAngle += -0.005f;
            }
            else {
                //プレイヤー負け
                playerPy += 1.0f;
                playerAngle += 0.005f;
            }
            //勝ち負け文字を大きくしていく
            if (resultSize < 180) {
                resultSize += 10.0f;
            }
            //ゲームステート切り替え-------------------------------------------
            if (isTrigger(KEY_SPACE)) {
                state = INIT;
            }
        }
        //描画-----------------------------------------------------------------
        clear(200);
        print(playerHand);
        //プレイヤーの手
        rectMode(CENTER);
        imageColor(playerR, playerG, playerB);
        image(playerImg, playerPx, playerPy,playerAngle);
        //ＰＣの手
        imageColor(pcR, pcG, pcB);
        image(pcImg, pcPx, pcPy,pcAngle);
        //プレイヤーハート
        imageColor(255, 0, 0);
        for (int i = 0; i < playerLife; i++) {
            image(heartImg, playerPx - 50 + i * 50, playerPy - 110);
        }
        //ＰＣハート
        for (int i = 0; i < pcLife; i++) {
            image(heartImg, pcPx - 50 + i * 50, pcPy - 110);
        }
        //勝ち負けテキスト
        if (state == RESULT) {
            textSize(resultSize);
            if (playerLife > 0) {
                fill(255, 0, 0);
                text("勝ち", resultPx, resultPy);
            }
            else {
                fill(0, 0, 200);
                text("負け", resultPx, resultPy);
            }
        }
    }
}

#endif

