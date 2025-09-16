# Woody-Woodpacker

## packing?
コードを圧縮、難読化して、ウイルス対策を回避。
読み込まれる時には、
1. 圧縮されてオリジナルコードの展開
1. オリジナルコードのローダー役の再構築

## flow
1. パックするプログラムの読み込み
1. ELFファイルの情報収集
1. テキストセグメントの暗号化
1. 展開ルーチンの作成・埋め込み
1. ELFファイル・ヘッダの修正
1. パック済みプログラムの書き出し

## decoder_stub creation
1. `nasm -f bin <file.s>`
1. `xxd -i <decoder.bin> > decoder_stub.h`

## refrence
アナライジング・マルウェア
