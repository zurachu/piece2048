#if !defined( ZURAPCE_LCD_H )
#define ZURAPCE_LCD_H

/** @file
	LCD 関連.
	@author zurachu
*/

/**
	画面関係の初期化.
	@retval 1 仮想画面バッファ確保成功
	@retval 0 仮想画面バッファ確保失敗
*/
int Lcd_Init( void );

/**
	LCD 更新フラグを立てる.
*/
void Lcd_Update( void );

/**
	仮想画面バッファの内容を LCD に転送.
	LCD 更新フラグが立っていなければ転送を行わないので、
	毎フレーム呼び出して下さい。
*/
void Lcd_Trans( void );

#endif // !defined( ZURAPCE_LCD_H )
