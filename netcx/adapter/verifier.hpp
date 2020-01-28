// Copyright (C) Microsoft Corporation. All rights reserved.

/*++

Abstract:
    Contains definitions used by NetAdapterCx to detect and report violations

--*/

#pragma once

struct AdapterExtensionInit;
struct AdapterInit;
struct QUEUE_CREATION_CONTEXT;
struct NX_PRIVATE_GLOBALS;

struct _NET_ADAPTER_OFFLOAD_LSO_CAPABILITIES;
typedef _NET_ADAPTER_OFFLOAD_LSO_CAPABILITIES NET_ADAPTER_OFFLOAD_LSO_CAPABILITIES;

struct _NET_REQUEST_QUEUE_CONFIG;
typedef _NET_REQUEST_QUEUE_CONFIG NET_REQUEST_QUEUE_CONFIG;

struct _NET_ADAPTER_PACKET_FILTER_CAPABILITIES;
typedef _NET_ADAPTER_PACKET_FILTER_CAPABILITIES NET_ADAPTER_PACKET_FILTER_CAPABILITIES;

class NxAdapter;
class NxAdapterCollection;
class NxDevice;
class NxRequest;

#define NDIS_MBB_WAKEUP_SUPPORTED_FLAGS ( \
    NDIS_WWAN_WAKE_ON_REGISTER_STATE_SUPPORTED | \
    NDIS_WWAN_WAKE_ON_SMS_RECEIVE_SUPPORTED | \
    NDIS_WWAN_WAKE_ON_USSD_RECEIVE_SUPPORTED | \
    NDIS_WWAN_WAKE_ON_PACKET_STATE_SUPPORTED | \
    NDIS_WWAN_WAKE_ON_UICC_CHANGE_SUPPORTED) \

#define NDIS_WIFI_WAKEUP_SUPPORTED_FLAGS ( \
    NDIS_WLAN_WAKE_ON_NLO_DISCOVERY_SUPPORTED | \
    NDIS_WLAN_WAKE_ON_AP_ASSOCIATION_LOST_SUPPORTED | \
    NDIS_WLAN_WAKE_ON_GTK_HANDSHAKE_ERROR_SUPPORTED | \
    NDIS_WLAN_WAKE_ON_4WAY_HANDSHAKE_REQUEST_SUPPORTED) \

#define NET_PACKET_FILTER_SUPPORTED_FLAGS ( \
    NetPacketFilterFlagDirected | \
    NetPacketFilterFlagMulticast | \
    NetPacketFilterFlagAllMulticast | \
    NetPacketFilterFlagBroadcast | \
    NetPacketFilterFlagPromiscuous)

#define NDIS_AUTO_NEGOTIATION_SUPPORTED_FLAGS ( \
    NetAdapterAutoNegotiationFlagXmitLinkSpeedAutoNegotiated | \
    NetAdapterAutoNegotiationFlagRcvLinkSpeedautoNegotiated | \
    NetAdapterAutoNegotiationFlagDuplexAutoNegotiated | \
    NetAdapterAutoNegotiationFlagPauseFunctionsAutoNegotiated)

#define NET_CONFIGURATION_QUERY_ULONG_SUPPORTED_FLAGS ( \
    NET_CONFIGURATION_QUERY_ULONG_NO_FLAGS | \
    NET_CONFIGURATION_QUERY_ULONG_MAY_BE_STORED_AS_HEX_STRING)

//
// This macro is used to check if an input flag mask contains only allowed flag values, as defined by _supported
//
#define VERIFIER_CHECK_FLAGS(_flags, _supported) (((_flags) & ~(_supported)) == 0)

//
// NetAdapterCx failure codes
//
typedef enum _FailureCode : ULONG_PTR
{
    FailureCode_CorruptedPrivateGlobals = 0,
    FailureCode_IrqlIsNotPassive,
    FailureCode_IrqlNotLessOrEqualDispatch,
    FailureCode_AdapterAlreadyStarted,
    FailureCode_EvtArmDisarmWakeNotInProgress,
    FailureCode_CompletingNetRequestWithPendingStatus,
    FailureCode_InvalidNetRequestType,
    FailureCode_DefaultRequestQueueAlreadyExists,
    FailureCode_InvalidStructTypeSize,
    FailureCode_InvalidQueueConfiguration,
    FailureCode_MacAddressLengthTooLong,
    FailureCode_InvalidPacketFilterCapabilities,
    FailureCode_InvalidSetPacketFilterCallBack,
    FailureCode_InvalidLinkState,
    FailureCode_ParameterCantBeNull,
    FailureCode_InvalidQueryUlongFlag,
    FailureCode_QueueConfigurationHasError,
    FailureCode_InvalidRequestQueueType,
    FailureCode_MtuMustBeGreaterThanZero,
    FailureCode_BadQueueInitContext,
    FailureCode_CreatingNetQueueFromWrongThread,
    FailureCode_NetQueueInvalidConfiguration,
    FailureCode_ParentObjectNotNull,
    FailureCode_QueueAlreadyCreated,
    FailureCode_ObjectAttributesContextSizeTooLarge,
    FailureCode_NotPowerOfTwo,
    FailureCode_InvalidNetExtensionName,
    FailureCode_InvalidNetExtensionVersion,
    FailureCode_InvalidNetExtensionType,
    FailureCode_InvalidNetExtensionAlignment,
    FailureCode_InvalidNetExtensionExtensionSize,
    FailureCode_InvalidAdapterTxCapabilities,
    FailureCode_InvalidAdapterRxCapabilities,
    FailureCode_InvalidReceiveScalingHashType,
    FailureCode_InvalidReceiveScalingProtocolType,
    FailureCode_InvalidReceiveScalingEncapsulationType,
    FailureCode_RemovingDeviceWithAdapters,
    FailureCode_InvalidDatapathCallbacks,
    FailureCode_InvalidNetAdapterInitSignature,
    FailureCode_NetAdapterInitAlreadyUsed,
    FailureCode_InvalidNetAdapterExtensionInitSignature,
    FailureCode_InvalidLsoCapabilities,
    FailureCode_IllegalPrivateApiCall,
    FailureCode_InvalidQueueHandle,
    FailureCode_InvalidNetAdapterWakeReasonMediaChange,
    FailureCode_PowerNotInTransition,
    FailureCode_DisarmNotInProgress,
    FailureCode_InvalidPowerOffloadListSignature,
    FailureCode_InvalidWakeSourceListSignature,
    FailureCode_InvalidRingImmutable,
    FailureCode_InvalidRingImmutableFrameworkElement,
    FailureCode_InvalidRingImmutableDriverTxPacket,
    FailureCode_InvalidRingImmutableDriverTxFragment,
    FailureCode_InvalidRingImmutableDriverRxPacketIgnore,
    FailureCode_InvalidRingModifiedRxPacket,
    FailureCode_InvalidRingModifiedRxFragment,
    FailureCode_InvalidRingUnmodifiedRxPacket,
    FailureCode_InvalidRingUnmodifiedRxFragment,
    FailureCode_InvalidRingBeginIndex,
    FailureCode_InvalidRingRxPacketFragmentCountZero,
    FailureCode_InvalidRingRxPacketFragmentCountOutOfRange,
    FailureCode_InvalidRingRxPacketFragmentIndexOutOfPreRange,
    FailureCode_InvalidRingRxPacketFragmentCountOutOfPreRange,
    FailureCode_InvalidRingRxPacketFragmentIndexOutOfPostRange,
    FailureCode_InvalidRingRxPacketFragmentCountOutOfPostRange,
    FailureCode_InvalidRingRxPacketLayer2Type,
    FailureCode_InvalidRingRxPacketLayer2TypeNullLengthNonZero,
    FailureCode_InvalidRingRxPacketLayer2TypeEthernetLengthInvalid,
    FailureCode_InvalidRingRxPacketLayer3TypeIPv4LengthInvalid,
    FailureCode_InvalidRingRxPacketLayer3TypeIPv6LengthInvalid,
    FailureCode_InvalidRingRxPacketLayer4TypeTcpLengthInvalid,
    FailureCode_InvalidRingRxPacketLayer4TypeUdpLengthInvalid,
    FailureCode_InvalidRingRxPacketLayer3Type,
    FailureCode_InvalidRingRxPacketLayer4Type,
    FailureCode_InvalidRingRxPacketFragmentIndexOverlap,
    FailureCode_InvalidRingRxPacketFragmentCountOverlap,
    FailureCode_InvalidRingRxPacketFragmentOffsetInvalid,
    FailureCode_InvalidRingRxPacketFragmentLengthInvalid,
    FailureCode_InvalidMediaSpecificWakeUpFlags,
    FailureCode_InvalidOidRequestDispatchSignature,
} FailureCode;

//
// Verifier_ReportViolation uses a value from this enum to decide what to do in case of a violation
//
// Verifier_Verify* functions that use only VerifierAction_BugcheckAlways should not return any value.
// Verifier_Verify* functions that use VerifierAction_DbgBreakIfDebuggerPresent at least one time should return NTSTATUS, and the caller should deal with the status
//
typedef enum _VerifierAction
{
    VerifierAction_BugcheckAlways,
    VerifierAction_DbgBreakIfDebuggerPresent
} VerifierAction;

void
NetAdapterCxBugCheck(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ FailureCode FailureCode,
    _In_ ULONG_PTR Parameter2,
    _In_ ULONG_PTR Parameter3
);

void
Verifier_ReportViolation(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ VerifierAction Action,
    _In_ FailureCode FailureCode,
    _In_ ULONG_PTR Parameter2,
    _In_ ULONG_PTR Parameter3
);

void
Verifier_VerifyPrivateGlobals(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals
);

void
Verifier_VerifyIrqlPassive(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals
);

void
Verifier_VerifyIrqlLessThanOrEqualDispatch(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals
);

void
Verifier_VerifyAdapterNotStarted(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NxAdapter *         pNxAdapter
);

void
Verifier_VerifyNetPowerTransition(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NxDevice * Device
);

void
Verifier_VerifyNetPowerUpTransition(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NxDevice * Device
);

void
Verifier_VerifyNetRequestCompletionStatusNotPending(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NETREQUEST NetRequest,
    _In_ NTSTATUS CompletionStatus
);

void
Verifier_VerifyNetRequestType(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NxRequest * NxRequest,
    _In_ NDIS_REQUEST_TYPE Type
);

void
Verifier_VerifyNetRequestIsQuery(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NxRequest * NxRequest
);

void
Verifier_VerifyNetRequest(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NxRequest * pNxRequest
);

template <typename T>
void
Verifier_VerifyTypeSize(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ T * Input
)
{
    ULONG uInputSize = Input->Size;
    ULONG uExpectedSize = sizeof(T);

    if (uInputSize != uExpectedSize)
    {
        Verifier_ReportViolation(
            PrivateGlobals,
            VerifierAction_BugcheckAlways,
            FailureCode_InvalidStructTypeSize,
            uInputSize,
            uExpectedSize);
    }
}

void
Verifier_VerifyNotNull(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ void const * const Ptr
);

NTSTATUS
Verifier_VerifyQueueConfiguration(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NET_REQUEST_QUEUE_CONFIG * QueueConfig
);

void
Verifier_VerifyReceiveScalingCapabilities(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ const NET_ADAPTER_RECEIVE_SCALING_CAPABILITIES * Capabilities
);

void
Verifier_VerifyPacketFilter(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NET_ADAPTER_PACKET_FILTER_CAPABILITIES const * PacketFilter
);

void
Verifier_VerifyCurrentLinkState(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NET_ADAPTER_LINK_STATE * LinkState
);

void
Verifier_VerifyLinkLayerAddress(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NET_ADAPTER_LINK_LAYER_ADDRESS *LinkLayerAddress
);

void
Verifier_VerifyQueryAsUlongFlags(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NET_CONFIGURATION_QUERY_ULONG_FLAGS Flags
);

void
Verifier_VerifyMtuSize(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
     ULONG MtuSize
);

void
Verifier_VerifyQueueInitContext(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ QUEUE_CREATION_CONTEXT * NetQueueInit
);

void
Verifier_VerifyNetPacketQueueConfiguration(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NET_PACKET_QUEUE_CONFIG const * Configuration
);

void
Verifier_VerifyObjectAttributesParentIsNull(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ WDF_OBJECT_ATTRIBUTES * ObjectAttributes
);

void
Verifier_VerifyObjectAttributesContextSize(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_opt_ WDF_OBJECT_ATTRIBUTES * ObjectAttributes,
    _In_ SIZE_T MaximumContextSize
);

void
Verifier_VerifyDatapathCallbacks(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NET_ADAPTER_DATAPATH_CALLBACKS const * DatapathCallbacks
);

void
Verifier_VerifyAdapterInitSignature(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ AdapterInit const * AdapterInit
);

void
Verifier_VerifyAdapterExtensionInitSignature(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ AdapterExtensionInit const * AdapterExtensionInit
);

void
Verifier_VerifyAdapterInitNotUsed(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ AdapterInit const * AdapterInit
);

void
Verifier_VerifyNetExtensionQuery(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NET_EXTENSION_QUERY const * Query
);

void
Verifier_VerifyNetAdapterTxCapabilities(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ const NET_ADAPTER_TX_CAPABILITIES *TxCapabilities
);

void
Verifier_VerifyNetAdapterRxCapabilities(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ const NET_ADAPTER_RX_CAPABILITIES * RxCapabilities
);

void
Verifier_VerifyDeviceAdapterCollectionIsEmpty(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NxDevice const * Device,
    _In_ NxAdapterCollection const * AdapterCollection
);

void
Verifier_VerifyLsoCapabilities(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NET_ADAPTER_OFFLOAD_LSO_CAPABILITIES const * LsoCapabilities
);

void
Verifier_VerifyExtensionGlobals(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals
);

void
Verifier_VerifyRxQueueHandle(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NETPACKETQUEUE NetRxQueue
);

void
Verifier_VerifyTxQueueHandle(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NETPACKETQUEUE NetTxQueue
);

void
Verifier_VerifyPowerOffloadList(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NET_POWER_OFFLOAD_LIST const * List
);

void
Verifier_VerifyWakeSourceList(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NET_WAKE_SOURCE_LIST const * List
);

void
Verifier_VerifyRingImmutable(
    _In_ NX_PRIVATE_GLOBALS const & PrivateGlobals,
    _In_ NET_RING const & Before,
    _In_ NET_RING const & After
);

void
Verifier_VerifyRingImmutableDriverTxPackets(
    _In_ NX_PRIVATE_GLOBALS const & PrivateGlobals,
    _In_ NET_RING const & Before,
    _In_ NET_RING const & After
);

void
Verifier_VerifyRingImmutableDriverTxFragments(
    _In_ NX_PRIVATE_GLOBALS const & PrivateGlobals,
    _In_ NET_RING const & Before,
    _In_ NET_RING const & After
);

void
Verifier_VerifyRingImmutableDriverRx(
    _In_ NX_PRIVATE_GLOBALS const & PrivateGlobals,
    _In_ NET_ADAPTER_RX_CAPABILITIES const & RxCapabilities,
    _In_ NET_RING const & PacketBefore,
    _In_ NET_RING const & PacketAfter,
    _In_ NET_RING const & FragmentBefore,
    _In_ NET_RING const & FragmentAfter
);

void
Verifier_VerifyRingBeginIndex(
    _In_ NX_PRIVATE_GLOBALS const & PrivateGlobals,
    _In_ NET_RING const & Before,
    _In_ NET_RING const & After
);

void
Verifier_VerifyRingImmutableFrameworkElements(
    _In_ NX_PRIVATE_GLOBALS const & PrivateGlobals,
    _In_ NET_RING const & Before,
    _In_ NET_RING const & After
);

void
Verifier_VerifyNdisPmCapabilities(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ NET_ADAPTER_NDIS_PM_CAPABILITIES const * NdisPmCapabilities
);

void
Verifier_VerifyOidRequestDispatchSignature(
    _In_ NX_PRIVATE_GLOBALS const * PrivateGlobals,
    _In_ WDFCONTEXT Context,
    _In_ ULONG ExpectedSignature
);
