/**
 * @file atomic.hpp
 * @author Nishinaga
 * @brief Atomic変数を実現するクラスの定義
 * @version 0.1
 * @date 2023-09-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <concepts>
#include <utility>
#include <memory>

template <std::copyable Copyable>
class Atomic
{
public:
    /**
     * @brief Construct a new Atomic object
     * 
     */
    Atomic(const Copyable);

    /**
     * @brief Construct a new Atomic object
     *        ムーブ代入のみ許可する
     * 
     */
    Atomic(const Atomic&&);

    ~Atomic();

    /**
     * @brief 本来はロックフリーであることを示すが、
     *        ミューテックスによるデッドロックが
     *        起こりえないので常にtrueを返す
     * 
     * @return true always
     * @return false none
     */
    bool isLockFree();
    
    /**
     * @brief 値を書き込む
     * 
     * @param cp 書き込む値
     */
    void Store(const Copyable cp);

    /**
     * @brief 値を読み出す
     * 
     * @return Copyable 読み出された値
     */
    Copyable Load();

    /**
     * @brief キャスト可能な型にキャストする
     * 
     * @tparam T キャスト可能な型
     * @return T キャストされた保持されている値
     */
    template<typename T>
    operator T();

    /**
     * @brief 値を交換する
     * 
     * @param desired 入れ替える値
     * @return Copyable もと入っている値
     */
    Copyable Exchange(const Copyable desired);

    /**
     * @brief 保持している値が期待した値だった場合、保持している値を更新し、trueを返す
     *        そうでなければ保持している値を更新せずにfalseを返す
     * 
     * @param expected 期待される値
     * @param desired 代入する値
     * @return true 値の更新に成功
     * @return false 値の更新に失敗
     */
    bool CompareExchange(const Copyable& expected, const Copyable desired);

private:
    Copyable m_entity;

    Atomic(Atomic&) = delete;
    void operator = (Atomic&) = delete;
    void operator = (Atomic&&) = delete;
};
