#if !defined( ZURAPCE_LDIRECT_H )
#define ZURAPCE_LDIRECT_H

/** @file
	16階調描画関連.
	液晶の残像を利用して、5枚の画像を高速に切り替え、16階調の画像を表示しているようにみせかけます。
	さらに、通常の４階調仮想画面バッファを重ね合わせて表示できます。
	
	処理が重いですが、コードを高速 RAM に配置することで高速化できます。
	project.mak の USE_LDIRECT_ON_FRAM := true を有効にして、
	pceAppInit() の先頭で FramObject_Init() を呼び出して下さい。
	
	@see @ref pgx_format

	@author zurachu
*/

#include <piece.h>

/** @page pgx_format 16階調画像フォーマット
	PIECE_BMP の拡張フォーマットです。

	構造体は PIECE_BMP をそのまま使うため、
	通常の PIECE_BMP と同様に PieceBmp_Construct() で初期化できます。
	元データとしては、 16階調 BMP を pgd16cnv で変換したものを渡してください。
	https://github.com/zurachu/pgd16cnv

@code
	typedef struct {
		DWORD head; // 識別子 'PBEX'（既存アプリの誤動作防止）
		DWORD fsize; // ファイル長
		BYTE bpp; // bit 深度 (4)
		BYTE mask; // マスクの bit 深度 (1)
		int w; // X 幅 8 ピクセル単位厳守
		int h; // Y 高さ
		DWORD buf_size; // BMP サイズ = ( bpp + mask ) * w * h / 8
	} PBMP_FILEHEADER;
	
	typedef struct {
		PBMP_FILEHEADER	header;
		BYTE *buf; // 4 BIT 1 ピクセル
		BYTE *mask; // 1 BIT 1 ピクセル
	} PIECE_BMP;
@endcode
*/

/**
	初期化.
	16階調用仮想画面バッファおよび LCD ダイレクト転送用バッファ（5枚）を確保します。
	@retval 1 バッファ確保成功
	@retval 0 バッファ確保失敗
*/
int Ldirect_Init( void );

/**
	16階調用仮想画面バッファのアドレスを取得.
	バッファの構造は、通常の４階調用仮想画面バッファと同じです。
	1ドット1バイト（下位4ビットのみ使用＝16色）
	横128ドット×縦88ドット = 11246バイト
@verbatim
Ldirect_Buffer()→+---------... ...------------+
                  |                            |
                  |                            |  ↑
                  .                            .
                  .                            .  Y 88 ドット
                  .                            .
                  |                            |  ↓
                  |                            |
                  +---------... ...------------+
                         ← X 128 ドット→
@endverbatim
*/
BYTE* Ldirect_Buffer( void );

/**
	LCD ダイレクト転送用バッファを更新します.
	実際には、内部で更新フラグを立てるだけで、
	Ldirect_Trans() で1フレーム1枚ずつ、
	16階調用仮想画面、４階調用仮想画面を LCD ダイレクト転送用バッファに転送します。
*/
void Ldirect_Update( void );

/**
	Ldirect_Trans() で４階調用仮想画面バッファを LCD ダイレクト転送用バッファに
	転送するかどうかを設定します.
	@param visible フラグ
*/
void Ldirect_VBuffView( BOOL visible );

/**
	LCD ダイレクト転送.
	LCD ダイレクト転送用バッファを切り替えて、 LCD バッファに転送します。
	毎フレーム呼び出して下さい。
	Ldirect_Update() が呼び出されてから
	まだ LCD ダイレクト転送用バッファが更新されていない場合、
	16階調用仮想画面、４階調用仮想画面を LCD ダイレクト転送用バッファに
	転送してから転送します。
*/
void Ldirect_Trans( void );

/**
	４階調用仮想画面バッファを透過色（COLOR_MASK）で塗り潰す.
	P/ECE 開発環境のドキュメント「ハードウェア概要」より
	仮想画面バッファは下位2ビットのみ使用、
	上位ビットに０以外が書き込まれていた場合の動作は保証無しとあるため、
	これを呼び出す場合は必ず Ldirect の重ね合わせ表示を使ってください。
	@param x 左上 X 座標
	@param y 左上 Y 座標
	@param w 幅
	@param h 高さ
*/
void Ldirect_VBuffClear( int x, int y, int w, int h );

/**
	16階調用仮想画面バッファに16階調画像を描画.
	@param p 16階調 PIECE_BMP へのポインタ
	@param dx 描画先左上 X 座標
	@param dy 描画先左上 Y 座標
	@param sx 描画元左上 X 座標
	@param sy 描画元左上 Y 座標
	@param width 幅
	@param height 高さ
	@retval 0 描画なし
	@retval 1 描画完了
	
	@see @ref pgx_format
*/
int Ldirect_DrawObject( PIECE_BMP const* p, int dx, int dy, int sx, int sy
						, int width, int height );

/**
	16階調用仮想画面バッファに点を描画.
	@param color 色
	@param x X座標
	@param y Y座標
*/
void Ldirect_Point( BYTE color, int const x, int const y );

/**
	16階調用仮想画面バッファに矩形を描画.
	@param color 色
	@param x 左上X座標
	@param y 左上Y座標
	@param width 幅
	@param height 高さ
*/
void Ldirect_Paint( BYTE color, int x, int y, int width, int height );

#endif	// !defined( ZURAPCE_LDIRECT_H )
