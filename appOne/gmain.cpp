#if 1
#include"libOne.h"
struct DATA {
    //�v���C���[�f�[�^
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
    //�����f�[�^
    int pcHand;
    int pcImage;
    float pcPx;
    float pcPy;
    float pcAngle;
    float pcR;
    float pcG;
    float pcB;
    int pcLife;
    //������������
    float resultPx;
    float resultPy;
    float resultSize;
    //��Ԃ̐؂�ւ�
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
    //�����f�[�^
  d->pcHand = d->GU;
  d->pcImage = d->pcGUImage;
  d->pcPx = 550;
  d->pcPy = 225;
  d->pcAngle = 0;
  d->pcR = 255;
  d->pcG = 255;
  d->pcB = 255;
  d->pcLife = 3;
    //������������
  d->resultPx = 225;
  d->resultPy = 320;
  d->resultSize = 0;
    //�Q�[���X�e�[�g�؂�ւ�
  d->state = d->PLAY;
}
void play(struct DATA* d) {
    if (isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {
        //�v���C���[�̎�����߂�
        if (isTrigger(KEY_A)) { d->playerHand = d->GU; }
        else if (isTrigger(KEY_S)) { d->playerHand = d->CHOKI; }
        else if (isTrigger(KEY_D)) { d->playerHand = d->PA; }
        //�v���C���[�̉摜��؂�ւ���
        if (d->playerHand == d->GU) { d->playerImage = d->playerGUImage; }
        else if (d->playerHand == d->CHOKI) { d->playerImage = d->playerCHOKIImage; }
        else if (d->playerHand == d->PA) {d->playerImage = d->playerPAImage; }
        //�����̎�����߂�
        d->pcHand = random() % 3;
        //�����̉摜��؂�ւ���
        if (d->pcHand == d->GU) { d->pcImage = d->pcGUImage; }
        else if (d->pcHand == d->CHOKI) { d->pcImage = d->pcCHOKIImage; }
        else if (d->pcHand == d->PA) { d->pcImage = d->pcPAImage; }
        //���������𔻒肵�A�F��ς���
        if (d->playerHand == d->pcHand) {//������
            d->playerR = 255; d->playerG = 255; d->playerB = 255;
            d->pcR = 255; d->pcG = 255; d->pcB = 255;
        }
        else if ((d->playerHand + 1) % 3 == d->pcHand) {//�v���C���[�̏���
            d->playerR = 255; d->playerG = 200; d->playerB = 200;
            d->pcR = 255; d->pcG = 255; d->pcB = 255;
            d->pcLife--;
        }
        else { //�����̏���
            d->playerR = 255; d->playerG= 255; d->playerB = 255;
            d->pcR = 255; d->pcG = 200; d->pcB = 200;
            d->playerLife--;
        }
        //�Q�[���X�e�[�g�̐؂�ւ�
        if (d->playerLife == 0 ||d->pcLife == 0) {
            d->state = d->RESULT;
        }
    }
}
void result(struct DATA* d) {
        //�����̕���
        if (d->pcLife == 0) {
            d->pcPy += 1.0f;
            d->pcAngle += -0.005;
        }
        //�v���C���[�̕���
        else {
            d->playerPy += 1.0f;
            d->playerAngle += -0.005;
        }
        //���������������g�傷��
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
    //�v���C���[�̎�
    imageColor(d->playerR, d->playerG, d->playerB);
    image(d->playerImage, d->playerPx, d->playerPy, d->playerAngle);
    //pc�̎�
    imageColor(d->pcR, d->pcG, d->pcB);
    image(d->pcImage, d->pcPx, d->pcPy, d->pcAngle);
    //�v���C���[�n�[�g
    imageColor(255, 0, 0);
    for (int i = 0; i < d->playerLife; i++) {
        image(d->heartImage, d->playerPx - 50 + i * 50, d->playerPy - 110);
    }
    //�����n�[�g
    imageColor(255, 0, 0);
    for (int i = 0; i < d->pcLife; i++) {
        image(d->heartImage, d->pcPx - 50 + i * 50, d->pcPy - 110);
    }

    if (d->state == d->RESULT) {
        textSize(d->resultSize);
        if (d->playerLife > 0) {
            fill(255, 0, 0);
            text("����", d->resultPx, d->resultPy);
        }
        else {
            fill(0, 0, 200);
            text("����", d->resultPx, d->resultPy);
        }
    }
}
#include"libOne.h"
void gmain() {
    //�E�B���h�E�\��
    window(800, 450);
    struct DATA d;
    //�摜�̓ǂݍ���
    loadImges(&d);
    //���C�����[�v
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
    //�E�B���h�E�\��
    window(800, 450);
    //�摜�ǂݍ���
    int playerGuImg    = loadImage("assets\\playerGu.png");
    int playerChokiImg = loadImage("assets\\playerChoki.png");
    int playerPaImg    = loadImage("assets\\playerPa.png");
    int pcGuImg        = loadImage("assets\\pcGu.png");
    int pcChokiImg     = loadImage("assets\\pcChoki.png");
    int pcPaImg        = loadImage("assets\\pcPa.png");
    int heartImg       = loadImage("assets\\heart.png");
    //��̔ԍ������߂Ă���
    int GU = 0;
    int CHOKI = 1;
    int PA = 2;
    //�v���C���[�f�[�^
    int playerHand;
    int playerImg;
    float playerPx;
    float playerPy;
    float playerAngle;
    float playerR;
    float playerG;
    float playerB;
    int playerLife;
    //�o�b�f�[�^
    int pcHand;
    int pcImg;
    float pcPx;
    float pcPy;
    float pcAngle;
    float pcR;
    float pcG;
    float pcB;
    int pcLife;
    //�������������p
    float resultPx;
    float resultPy;
    float resultSize;
    //��Ԑ؂�ւ�
    int INIT   = 0;
    int PLAY   = 1;
    int RESULT = 2;
    int state = INIT;
    //���C�����[�v
    while (notQuit) {
        //�f�[�^�X�V-----------------------------------------------------------
        if (state == INIT) {
            //�������O�����l�ݒ�
            //�v���C���[�f�[�^
            playerHand = GU;
            playerImg = playerChokiImg;
            playerPx = 250;
            playerPy = 225;
            playerAngle = 0;
            playerR = 255;
            playerG = 255;
            playerB = 255;
            playerLife = 3;
            //�o�b�f�[�^
            pcHand = GU;
            pcImg = pcChokiImg;
            pcPx = 550;
            pcPy = 225;
            pcAngle = 0;
            pcR = 255;
            pcG = 255;
            pcB = 255;
            pcLife = 3;
            //������������
            resultPx = 225;
            resultPy = 320;
            resultSize = 0;
            //�Q�[���X�e�[�g�؂�ւ�
            state = PLAY;
        }
        else if( state == PLAY ){
            //������-----------------------------------------------------------
            //A,S,D�����ꂩ�̃L�[�������ꂽ��
            if (isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {
                //�v���C���[�̎�����߂�---------------------------------------
                if      (isTrigger(KEY_A)) { playerHand = GU; }
                else if (isTrigger(KEY_S)) { playerHand = CHOKI; }
                else if (isTrigger(KEY_D)) { playerHand = PA; }
                //�v���C���[�̉摜��؂�ւ���
                if      (playerHand == GU   ) { playerImg = playerGuImg; }
                else if (playerHand == CHOKI) { playerImg = playerChokiImg; }
                else if (playerHand == PA   ) { playerImg = playerPaImg; }
                //�o�b�̎�����߂�---------------------------------------------
                pcHand = random() % 3;
                //�o�b�̉摜��؂�ւ���
                if      (pcHand == GU   ) { pcImg = pcGuImg; }
                else if (pcHand == CHOKI) { pcImg = pcChokiImg; }
                else if (pcHand == PA   ) { pcImg = pcPaImg; }
                //�����������肵�A�F��ς���-----------------------------------
                if (playerHand == pcHand) {
                    //������
                    playerR = 255; playerG = 255; playerB = 255;
                    pcR = 255; pcG = 255; pcB = 255;
                }
                else if ((playerHand + 1) % 3 == pcHand) {
                    //�v���C���[����
                    playerR = 255; playerG = 200; playerB = 200;
                    pcR = 255; pcG = 255; pcB = 255;
                    pcLife--;
                }
                else {
                    //�o�b����
                    playerR = 255; playerG = 255; playerB = 255;
                    pcR = 255; pcG = 200; pcB = 200;
                    playerLife--;
                }
                //�Q�[���X�e�[�g�؂�ւ�---------------------------------------
                if (playerLife == 0 || pcLife == 0) {
                    state = RESULT;
                }
            }
        }
        else if(state == RESULT){
            //�����I��---------------------------------------------------------
            if (pcLife == 0) {
                //�o�b����
                pcPy += 1.0f;
                pcAngle += -0.005f;
            }
            else {
                //�v���C���[����
                playerPy += 1.0f;
                playerAngle += 0.005f;
            }
            //��������������傫�����Ă���
            if (resultSize < 180) {
                resultSize += 10.0f;
            }
            //�Q�[���X�e�[�g�؂�ւ�-------------------------------------------
            if (isTrigger(KEY_SPACE)) {
                state = INIT;
            }
        }
        //�`��-----------------------------------------------------------------
        clear(200);
        print(playerHand);
        //�v���C���[�̎�
        rectMode(CENTER);
        imageColor(playerR, playerG, playerB);
        image(playerImg, playerPx, playerPy,playerAngle);
        //�o�b�̎�
        imageColor(pcR, pcG, pcB);
        image(pcImg, pcPx, pcPy,pcAngle);
        //�v���C���[�n�[�g
        imageColor(255, 0, 0);
        for (int i = 0; i < playerLife; i++) {
            image(heartImg, playerPx - 50 + i * 50, playerPy - 110);
        }
        //�o�b�n�[�g
        for (int i = 0; i < pcLife; i++) {
            image(heartImg, pcPx - 50 + i * 50, pcPy - 110);
        }
        //���������e�L�X�g
        if (state == RESULT) {
            textSize(resultSize);
            if (playerLife > 0) {
                fill(255, 0, 0);
                text("����", resultPx, resultPy);
            }
            else {
                fill(0, 0, 200);
                text("����", resultPx, resultPy);
            }
        }
    }
}

#endif

