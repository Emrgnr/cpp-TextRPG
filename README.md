- 강의나 책을 따라가면서 배운 내용들을 하나하나씩 TextRPG에 적용시켜보는 프로젝트.
- C++ 기본 문법부터 추후 게임 서버까지 붙이는게 주 목표

## 현재 시스템 구조
```mermaid
flowchart TD
	%% 메인 분기점
	main --> EnterTown
    main --> ChooseCharacter
    
    %% 캐릭터 선택 분기점
    ChooseCharacter --> GenerateCharacter
    GenerateCharacter -.-> EnterTown
    
    %% 광장 분기점
    EnterTown --> EnterField
    EnterTown --> EnterMyRoom
    EnterTown --> EnterShop
    
    %% 필드 분기점
    EnterField --> CreateMonster
    CreateMonster --> FightMonster
    
    %% 몬스터 전투 분기점
    FightMonster --> CalculateLevelupStat
    FightMonster --> CheckDropItem
    FightMonster -.-> EnterField
    
    %% 개인룸 분기점
    EnterMyRoom --> CheckPlayerEquipment
    EnterMyRoom --> CheckPlayerInventoryItem
    EnterMyRoom --> CheckPlayerStat
    
    %% 플레이어 장비 상호작용
    CheckPlayerEquipment --> EquipArmor
    CheckPlayerEquipment --> UnEquipArmor
	
	%% 플레이어 인벤토리 상호작용
	CheckPlayerInventoryItem --> CheckInventoryItemInfo
	CheckPlayerInventoryItem --> ChangeItemPosition
	CheckPlayerInventoryItem --> DeleteInventoryItem
	
	%% 상점 분기점
	EnterShop --> EnterItemBuyingState
	EnterShop --> EnterItemSellingState
	
	%% 상점 구매 상호작용
	EnterItemBuyingState --> BuyItemToShop
	
	%% 상점 판매 상호작용
	EnterItemSellingState --> SellItemToShop

```
