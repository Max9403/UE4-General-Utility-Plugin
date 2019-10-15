#include <CollisionQueryParams.h>
#include <EngineGlobals.h>
#include <Engine/GameEngine.h>
#include <DrawDebugHelpers.h>
#include <Kismet/KismetMathLibrary.h>
#include "GeneralUtilityBPLibrary.h"
#include "GeneralUtility.h"

bool UGeneralUtilityBPLibrary::ConeCapsuleTraceMultiForObject(UObject *WorldContextObject, FVector Location,
                                                              FVector Orientation, FRotator ViewRotation,
                                                              float Distance,
                                                              float HorizontalFieldOfView, float VerticalFieldOfView,
                                                              const TArray<TEnumAsByte<EObjectTypeQuery>> &ObjectTypes,
                                                              bool bTraceComplex,
                                                              const TArray<AActor *> &ActorsToIgnore,
                                                              EDrawDebugTrace::Type DrawDebugType,
                                                              TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                                              FLinearColor TraceColor, FLinearColor TraceHitColor,
                                                              FLinearColor ScanColor, FLinearColor ActorColor,
                                                              float DrawTime) {

    float TrueHalfHeight = FMath::Tan(FMath::DegreesToRadians(VerticalFieldOfView / 2.f)) * Distance;

    UKismetSystemLibrary::SphereTraceMultiForObjects(WorldContextObject,
                                                     Location + Orientation * TrueHalfHeight,
                                                     Location + (-1 * Orientation * TrueHalfHeight),
                                                     Distance, ObjectTypes, bTraceComplex, ActorsToIgnore,
                                                     DrawDebugType, OutHits, bIgnoreSelf, TraceColor,
                                                     TraceHitColor, DrawTime);

    if (OutHits.Num() > 0) {

        float top = ViewRotation.Pitch - (VerticalFieldOfView / 2.f);
        float left = ViewRotation.Yaw - (HorizontalFieldOfView / 2.f);

        UGeneralUtilityBPLibrary::FilterItemsIntoCone(WorldContextObject, Location, left, left + HorizontalFieldOfView,
                                                      top, top + VerticalFieldOfView, OutHits, DrawDebugType,
                                                      ActorColor, TraceHitColor, DrawTime);

#if ENABLE_DRAW_DEBUG
        UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
        if (DrawDebugType != EDrawDebugTrace::None) {
            ::DrawDebugAltCone(World, Location, ViewRotation, Distance, FMath::DegreesToRadians(HorizontalFieldOfView),
                               FMath::DegreesToRadians(VerticalFieldOfView), ScanColor.ToFColor(true),
                               DrawDebugType == EDrawDebugTrace::Persistent,
                               DrawDebugType == EDrawDebugTrace::ForDuration ? DrawTime : 0.f);
        }
#endif
    }
    return OutHits.Num() > 0;
}

bool UGeneralUtilityBPLibrary::ConeCapsuleTraceMultiByProfile(UObject *WorldContextObject, FVector Location,
                                                              FVector Orientation,
                                                              FRotator ViewRotation, float Distance,
                                                              float HorizontalFieldOfView, float VerticalFieldOfView,
                                                              FName ProfileName, bool bTraceComplex,
                                                              const TArray<AActor *> &ActorsToIgnore,
                                                              EDrawDebugTrace::Type DrawDebugType,
                                                              TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                                              FLinearColor TraceColor,
                                                              FLinearColor TraceHitColor,
                                                              FLinearColor ScanColor,
                                                              FLinearColor ActorColor,
                                                              float DrawTime) {
    float TrueHalfHeight = FMath::Tan(FMath::DegreesToRadians(VerticalFieldOfView / 2.f)) * Distance;

    UKismetSystemLibrary::SphereTraceMultiByProfile(WorldContextObject,
                                                    Location + Orientation * TrueHalfHeight,
                                                    Location + (-1 * Orientation * TrueHalfHeight),
                                                    Distance, ProfileName, bTraceComplex, ActorsToIgnore,
                                                    DrawDebugType, OutHits, bIgnoreSelf, TraceColor,
                                                    TraceHitColor, DrawTime);

    if (OutHits.Num() > 0) {
        float top = ViewRotation.Pitch - (VerticalFieldOfView / 2.f);
        float left = ViewRotation.Yaw - (HorizontalFieldOfView / 2.f);

        UGeneralUtilityBPLibrary::FilterItemsIntoCone(WorldContextObject, Location, left, left + HorizontalFieldOfView,
                                                      top, top + VerticalFieldOfView, OutHits, DrawDebugType,
                                                      ActorColor, TraceHitColor, DrawTime);

#if ENABLE_DRAW_DEBUG
        UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
        if (DrawDebugType != EDrawDebugTrace::None) {
            ::DrawDebugAltCone(World, Location, ViewRotation, Distance, FMath::DegreesToRadians(HorizontalFieldOfView),
                               FMath::DegreesToRadians(VerticalFieldOfView), ScanColor.ToFColor(true),
                               DrawDebugType == EDrawDebugTrace::Persistent,
                               DrawDebugType == EDrawDebugTrace::ForDuration ? DrawTime : 0.f);
        }
#endif
    }
    return OutHits.Num() > 0;
}

bool
UGeneralUtilityBPLibrary::ConeCapsuleTraceMultiByChannel(UObject *WorldContextObject, FVector Location,
                                                         FVector Orientation,
                                                         FRotator ViewRotation, float Distance,
                                                         float HorizontalFieldOfView, float VerticalFieldOfView,
                                                         ETraceTypeQuery TraceChannel, bool bTraceComplex,
                                                         const TArray<AActor *> &ActorsToIgnore,
                                                         EDrawDebugTrace::Type DrawDebugType,
                                                         TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                                         FLinearColor TraceColor,
                                                         FLinearColor TraceHitColor,
                                                         FLinearColor ScanColor,
                                                         FLinearColor ActorColor,
                                                         float DrawTime) {

    float TrueHalfHeight = FMath::Tan(FMath::DegreesToRadians(VerticalFieldOfView / 2.f)) * Distance;

    UKismetSystemLibrary::SphereTraceMulti(WorldContextObject,
                                           Location + Orientation * TrueHalfHeight,
                                           Location + (-1 * Orientation * TrueHalfHeight),
                                           Distance, TraceChannel, bTraceComplex, ActorsToIgnore,
                                           DrawDebugType, OutHits, bIgnoreSelf, TraceColor,
                                           TraceHitColor, DrawTime);

    if (OutHits.Num() > 0) {
        float top = ViewRotation.Pitch - (VerticalFieldOfView / 2.f);
        float left = ViewRotation.Yaw - (HorizontalFieldOfView / 2.f);

        UGeneralUtilityBPLibrary::FilterItemsIntoCone(WorldContextObject, Location, left, left + HorizontalFieldOfView,
                                                      top, top + VerticalFieldOfView, OutHits, DrawDebugType,
                                                      ActorColor, TraceHitColor, DrawTime);

#if ENABLE_DRAW_DEBUG
        UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
        if (DrawDebugType != EDrawDebugTrace::None) {
            ::DrawDebugAltCone(World, Location, ViewRotation, Distance, FMath::DegreesToRadians(HorizontalFieldOfView),
                               FMath::DegreesToRadians(VerticalFieldOfView), ScanColor.ToFColor(true),
                               DrawDebugType == EDrawDebugTrace::Persistent,
                               DrawDebugType == EDrawDebugTrace::ForDuration ? DrawTime : 0.f);
        }
#endif
    }
    return OutHits.Num() > 0;
}

bool UGeneralUtilityBPLibrary::ConeSphereTraceMultiForObject(UObject *WorldContextObject, FVector Location,
                                                             FRotator ViewRotation, float Distance,
                                                             float HorizontalFieldOfView, float VerticalFieldOfView,
                                                             const TArray<TEnumAsByte<EObjectTypeQuery>> &ObjectTypes,
                                                             bool bTraceComplex,
                                                             const TArray<AActor *> &ActorsToIgnore,
                                                             EDrawDebugTrace::Type DrawDebugType,
                                                             TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                                             FLinearColor TraceColor, FLinearColor TraceHitColor,
                                                             FLinearColor ScanColor, FLinearColor ActorColor,
                                                             float DrawTime) {
    UKismetSystemLibrary::SphereTraceMultiForObjects(WorldContextObject,
                                                     Location, Location,
                                                     Distance, ObjectTypes, bTraceComplex, ActorsToIgnore,
                                                     DrawDebugType, OutHits, bIgnoreSelf, TraceColor,
                                                     TraceHitColor, DrawTime);

    if (OutHits.Num() > 0) {

        float top = ViewRotation.Pitch - (VerticalFieldOfView / 2.f);
        float left = ViewRotation.Yaw - (HorizontalFieldOfView / 2.f);

        UGeneralUtilityBPLibrary::FilterItemsIntoCone(WorldContextObject, Location, left, left + HorizontalFieldOfView,
                                                      top, top + VerticalFieldOfView, OutHits, DrawDebugType,
                                                      ActorColor, TraceHitColor, DrawTime);

#if ENABLE_DRAW_DEBUG
        UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
        if (DrawDebugType != EDrawDebugTrace::None) {
            ::DrawDebugAltCone(World, Location, ViewRotation, Distance, FMath::DegreesToRadians(HorizontalFieldOfView),
                               FMath::DegreesToRadians(VerticalFieldOfView), ScanColor.ToFColor(true),
                               DrawDebugType == EDrawDebugTrace::Persistent,
                               DrawDebugType == EDrawDebugTrace::ForDuration ? DrawTime : 0.f);
        }
#endif
    }
    return OutHits.Num() > 0;
}

bool UGeneralUtilityBPLibrary::ConeSphereTraceMultiByProfile(UObject *WorldContextObject, FVector Location,
                                                             FRotator ViewRotation, float Distance,
                                                             float HorizontalFieldOfView, float VerticalFieldOfView,
                                                             FName ProfileName, bool bTraceComplex,
                                                             const TArray<AActor *> &ActorsToIgnore,
                                                             EDrawDebugTrace::Type DrawDebugType,
                                                             TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                                             FLinearColor TraceColor,
                                                             FLinearColor TraceHitColor,
                                                             FLinearColor ScanColor,
                                                             FLinearColor ActorColor,
                                                             float DrawTime) {
    UKismetSystemLibrary::SphereTraceMultiByProfile(WorldContextObject,
                                                    Location, Location,
                                                    Distance, ProfileName, bTraceComplex, ActorsToIgnore,
                                                    DrawDebugType, OutHits, bIgnoreSelf, TraceColor,
                                                    TraceHitColor, DrawTime);

    if (OutHits.Num() > 0) {
        float top = ViewRotation.Pitch - (VerticalFieldOfView / 2.f);
        float left = ViewRotation.Yaw - (HorizontalFieldOfView / 2.f);

        UGeneralUtilityBPLibrary::FilterItemsIntoCone(WorldContextObject, Location, left, left + HorizontalFieldOfView,
                                                      top, top + VerticalFieldOfView, OutHits, DrawDebugType,
                                                      ActorColor, TraceHitColor, DrawTime);

#if ENABLE_DRAW_DEBUG
        UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
        if (DrawDebugType != EDrawDebugTrace::None) {
            ::DrawDebugAltCone(World, Location, ViewRotation, Distance, FMath::DegreesToRadians(HorizontalFieldOfView),
                               FMath::DegreesToRadians(VerticalFieldOfView), ScanColor.ToFColor(true),
                               DrawDebugType == EDrawDebugTrace::Persistent,
                               DrawDebugType == EDrawDebugTrace::ForDuration ? DrawTime : 0.f);
        }
#endif
    }
    return OutHits.Num() > 0;
}

bool
UGeneralUtilityBPLibrary::ConeSphereTraceMultiByChannel(UObject *WorldContextObject, FVector Location,
                                                        FRotator ViewRotation, float Distance,
                                                        float HorizontalFieldOfView, float VerticalFieldOfView,
                                                        ETraceTypeQuery TraceChannel, bool bTraceComplex,
                                                        const TArray<AActor *> &ActorsToIgnore,
                                                        EDrawDebugTrace::Type DrawDebugType,
                                                        TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                                        FLinearColor TraceColor,
                                                        FLinearColor TraceHitColor,
                                                        FLinearColor ScanColor,
                                                        FLinearColor ActorColor,
                                                        float DrawTime) {
    UKismetSystemLibrary::SphereTraceMulti(WorldContextObject,
                                           Location, Location,
                                           Distance, TraceChannel, bTraceComplex, ActorsToIgnore,
                                           DrawDebugType, OutHits, bIgnoreSelf, TraceColor,
                                           TraceHitColor, DrawTime);

    if (OutHits.Num() > 0) {
        float top = ViewRotation.Pitch - (VerticalFieldOfView / 2.f);
        float left = ViewRotation.Yaw - (HorizontalFieldOfView / 2.f);

        UGeneralUtilityBPLibrary::FilterItemsIntoCone(WorldContextObject, Location, left, left + HorizontalFieldOfView,
                                                      top, top + VerticalFieldOfView, OutHits, DrawDebugType,
                                                      ActorColor, TraceHitColor, DrawTime);

#if ENABLE_DRAW_DEBUG
        UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
        if (DrawDebugType != EDrawDebugTrace::None) {
            ::DrawDebugAltCone(World, Location, ViewRotation, Distance, FMath::DegreesToRadians(HorizontalFieldOfView),
                               FMath::DegreesToRadians(VerticalFieldOfView), ScanColor.ToFColor(true),
                               DrawDebugType == EDrawDebugTrace::Persistent,
                               DrawDebugType == EDrawDebugTrace::ForDuration ? DrawTime : 0.f);
        }
#endif
    }
    return OutHits.Num() > 0;
}

bool UGeneralUtilityBPLibrary::ConeBoxTraceMultiForObject(UObject *WorldContextObject, FVector Location,
                                                          FRotator ViewRotation, float Distance,
                                                          float HorizontalFieldOfView, float VerticalFieldOfView,
                                                          const TArray<TEnumAsByte<EObjectTypeQuery>> &ObjectTypes,
                                                          bool bTraceComplex,
                                                          const TArray<AActor *> &ActorsToIgnore,
                                                          EDrawDebugTrace::Type DrawDebugType,
                                                          TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                                          FLinearColor TraceColor, FLinearColor TraceHitColor,
                                                          FLinearColor ScanColor, FLinearColor ActorColor,
                                                          float DrawTime) {
    FVector up = UKismetMathLibrary::GetUpVector(ViewRotation);
    FVector forward = UKismetMathLibrary::GetForwardVector(ViewRotation);

    FVector offset = forward * (Distance / 2.f);

    UKismetSystemLibrary::BoxTraceMultiForObjects(WorldContextObject,
                                                  Location + offset, Location + offset,
                                                  FVector(Distance / 2.f), forward.Rotation(), ObjectTypes,
                                                  bTraceComplex, ActorsToIgnore,
                                                  DrawDebugType, OutHits, bIgnoreSelf, TraceColor,
                                                  TraceHitColor, DrawTime);

    if (OutHits.Num() > 0) {

        float top = ViewRotation.Pitch - (VerticalFieldOfView / 2.f);
        float left = ViewRotation.Yaw - (HorizontalFieldOfView / 2.f);

        UGeneralUtilityBPLibrary::FilterItemsIntoCone(WorldContextObject, Location, left, left + HorizontalFieldOfView,
                                                      top, top + VerticalFieldOfView, OutHits, DrawDebugType,
                                                      ActorColor, TraceHitColor, DrawTime);

#if ENABLE_DRAW_DEBUG
        UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
        if (DrawDebugType != EDrawDebugTrace::None) {
            ::DrawDebugAltCone(World, Location, ViewRotation, Distance, FMath::DegreesToRadians(HorizontalFieldOfView),
                               FMath::DegreesToRadians(VerticalFieldOfView), ScanColor.ToFColor(true),
                               DrawDebugType == EDrawDebugTrace::Persistent,
                               DrawDebugType == EDrawDebugTrace::ForDuration ? DrawTime : 0.f);
        }
#endif
    }
    return OutHits.Num() > 0;
}

bool UGeneralUtilityBPLibrary::ConeBoxTraceMultiByProfile(UObject *WorldContextObject, FVector Location,
                                                          FRotator ViewRotation, float Distance,
                                                          float HorizontalFieldOfView, float VerticalFieldOfView,
                                                          FName ProfileName, bool bTraceComplex,
                                                          const TArray<AActor *> &ActorsToIgnore,
                                                          EDrawDebugTrace::Type DrawDebugType,
                                                          TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                                          FLinearColor TraceColor,
                                                          FLinearColor TraceHitColor,
                                                          FLinearColor ScanColor,
                                                          FLinearColor ActorColor,
                                                          float DrawTime) {

    FVector up = UKismetMathLibrary::GetUpVector(ViewRotation);
    FVector forward = UKismetMathLibrary::GetForwardVector(ViewRotation);

    FVector offset = forward * (Distance / 2.f);

    UKismetSystemLibrary::BoxTraceMultiByProfile(WorldContextObject, Location + offset, Location + offset,
                                                 FVector(Distance / 2.f), forward.Rotation(), ProfileName,
                                                 bTraceComplex, ActorsToIgnore,
                                                 DrawDebugType, OutHits, bIgnoreSelf, TraceColor,
                                                 TraceHitColor, DrawTime);

    if (OutHits.Num() > 0) {
        float top = ViewRotation.Pitch - (VerticalFieldOfView / 2.f);
        float left = ViewRotation.Yaw - (HorizontalFieldOfView / 2.f);

        UGeneralUtilityBPLibrary::FilterItemsIntoCone(WorldContextObject, Location, left, left + HorizontalFieldOfView,
                                                      top, top + VerticalFieldOfView, OutHits, DrawDebugType,
                                                      ActorColor, TraceHitColor, DrawTime);

#if ENABLE_DRAW_DEBUG
        UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
        if (DrawDebugType != EDrawDebugTrace::None) {
            ::DrawDebugAltCone(World, Location, ViewRotation, Distance, FMath::DegreesToRadians(HorizontalFieldOfView),
                               FMath::DegreesToRadians(VerticalFieldOfView), ScanColor.ToFColor(true),
                               DrawDebugType == EDrawDebugTrace::Persistent,
                               DrawDebugType == EDrawDebugTrace::ForDuration ? DrawTime : 0.f);
        }
#endif
    }
    return OutHits.Num() > 0;
}

bool
UGeneralUtilityBPLibrary::ConeBoxTraceMultiByChannel(UObject *WorldContextObject, FVector Location,
                                                     FRotator ViewRotation, float Distance,
                                                     float HorizontalFieldOfView, float VerticalFieldOfView,
                                                     ETraceTypeQuery TraceChannel, bool bTraceComplex,
                                                     const TArray<AActor *> &ActorsToIgnore,
                                                     EDrawDebugTrace::Type DrawDebugType,
                                                     TArray<FHitResult> &OutHits, bool bIgnoreSelf,
                                                     FLinearColor TraceColor,
                                                     FLinearColor TraceHitColor,
                                                     FLinearColor ScanColor,
                                                     FLinearColor ActorColor,
                                                     float DrawTime) {

    FVector up = UKismetMathLibrary::GetUpVector(ViewRotation);
    FVector forward = UKismetMathLibrary::GetForwardVector(ViewRotation);

    FVector offset = forward * (Distance / 2.f);

    UKismetSystemLibrary::BoxTraceMulti(WorldContextObject,
                                        Location + offset, Location + offset,
                                        FVector(Distance / 2.f), forward.Rotation(), TraceChannel, bTraceComplex,
                                        ActorsToIgnore, DrawDebugType, OutHits, bIgnoreSelf, TraceColor, TraceHitColor,
                                        DrawTime);

    if (OutHits.Num() > 0) {
        float top = ViewRotation.Pitch - (VerticalFieldOfView / 2.f);
        float left = ViewRotation.Yaw - (HorizontalFieldOfView / 2.f);

        UGeneralUtilityBPLibrary::FilterItemsIntoCone(WorldContextObject, Location, left, left + HorizontalFieldOfView,
                                                      top, top + VerticalFieldOfView, OutHits, DrawDebugType,
                                                      ActorColor, TraceHitColor, DrawTime);

#if ENABLE_DRAW_DEBUG
        UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
        if (DrawDebugType != EDrawDebugTrace::None) {
            ::DrawDebugAltCone(World, Location, ViewRotation, Distance, FMath::DegreesToRadians(HorizontalFieldOfView),
                               FMath::DegreesToRadians(VerticalFieldOfView), ScanColor.ToFColor(true),
                               DrawDebugType == EDrawDebugTrace::Persistent,
                               DrawDebugType == EDrawDebugTrace::ForDuration ? DrawTime : 0.f);
        }
#endif
    }
    return OutHits.Num() > 0;
}

void UGeneralUtilityBPLibrary::FilterItemsIntoCone(UObject *WorldContextObject, FVector Location, float LeftAngle,
                                                   float RightAngle,
                                                   float TopAngle, float BottomAngle, TArray<FHitResult> &OutHits,
                                                   EDrawDebugTrace::Type DrawDebugType,
                                                   FLinearColor ActorColor,
                                                   FLinearColor TraceHitColor,
                                                   float DrawTime) {

#if ENABLE_DRAW_DEBUG
    UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
#endif

    OutHits.RemoveAll([&](auto &hit) {
        if (hit.GetActor() != nullptr) {
            AActor *actor = hit.GetActor();
            FRotator angle = (actor->GetActorLocation() - Location).Rotation();

            bool isHit = TopAngle < angle.Pitch && BottomAngle > angle.Pitch
                         && LeftAngle < angle.Yaw && RightAngle > angle.Yaw;

#if ENABLE_DRAW_DEBUG
            if (DrawDebugType != EDrawDebugTrace::None) {
                ::DrawDebugLine(World, Location, actor->GetActorLocation(),
                                (isHit ? TraceHitColor : ActorColor).ToFColor(true),
                                DrawDebugType == EDrawDebugTrace::Persistent,
                                DrawDebugType == EDrawDebugTrace::ForDuration ? DrawTime : 0.f);
                ::DrawDebugPoint(World, actor->GetActorLocation(), 5,
                                 (isHit ? TraceHitColor : ActorColor).ToFColor(true),
                                 DrawDebugType == EDrawDebugTrace::Persistent,
                                 DrawDebugType == EDrawDebugTrace::ForDuration ? DrawTime : 0.f);
            }
#endif
            return !isHit;
        }
        return true;
    });
}


void UGeneralUtilityBPLibrary::DrawDebugCameraComponent(const UCameraComponent *CameraActor, FLinearColor CameraColor,
                                                        float Duration) {
#if ENABLE_DRAW_DEBUG
    if (CameraActor) {
        const FTransform transform = CameraActor->GetComponentToWorld();
        ::DrawDebugCamera(CameraActor->GetWorld(), transform.GetLocation(), transform.GetRotation().Rotator(),
                          CameraActor->FieldOfView, 10.0f, CameraColor.ToFColor(true), false, Duration, SDPG_World);
    }
#endif
}
